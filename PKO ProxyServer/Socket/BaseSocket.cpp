#include <event2\event.h>
#include <event2\buffer.h>
#include "BaseSocket.h"
#include "callback.h"

namespace PKO
{
	// Конструктор
	CBaseSocket::CBaseSocket(event_base *base, 
					size_t recv_buf_size, size_t send_buf_size)
	{
		// Создаем сокет
		m_fd = bufferevent_socket_new(base, INVALID_SOCKET, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setwatermark(m_fd, EV_READ | EV_WRITE, 2, 0);
		bufferevent_setcb(m_fd, cb_read, NULL, cb_event, this);
		
		// Создаем буферы для входящих и исходящих данных
		m_recv_buffer = new CNetBuffer(recv_buf_size);
		m_send_buffer = new CNetBuffer(send_buf_size);

		// Инициализируем размер блока
		m_block_size = 0;

		// Сокет отключен
		m_connected = false;

		// Сервер 
		m_server = false;
	}

	// Деструктор
	CBaseSocket::~CBaseSocket()
	{
		// Удаляем издателя 
		if (m_subject != nullptr) {
			delete m_subject;
		}

		// Удаляем буферы
		delete m_send_buffer;
		delete m_recv_buffer;

		// Удаляем сокет
		bufferevent_free(m_fd);
	}

	// Установить сокет
	void CBaseSocket::setSocket(evutil_socket_t socket)
	{
		m_connected = true;
		bufferevent_setfd(m_fd, socket);
		bufferevent_enable(m_fd, EV_READ | EV_WRITE);
	}

	// Установить IP адрес
	void CBaseSocket::setIpAddress(const std::string& ip_address)
	{
		m_ip_address = ip_address;
	}

	// Установить порт 
	void CBaseSocket::setPort(unsigned short int port)
	{
		m_port = port;
	}

	// Получить IP адрес
	const std::string& CBaseSocket::getIpAddress() const
	{
		return m_ip_address;
	}

	// Получить порт
	unsigned short int CBaseSocket::getPort() const
	{
		return m_port;
	}

	// Отправить данные
	void CBaseSocket::write(const char *data, size_t length)
	{
		bufferevent_write(m_fd, data, length);
	}

	// Подключен ли сокет
	bool CBaseSocket::connected() const
	{
		return m_connected;
	}

	// Закрыть соединение
	void CBaseSocket::close()
	{
		// Проверим, что сокет подключен
		if (!m_connected) {
			return;
		}

		evutil_socket_t sock = bufferevent_getfd(m_fd);

		// Разрываем соединение
		shutdown(sock, SD_BOTH);

		// Закрываем сокет
		evutil_closesocket(sock);

		// Вызываем событие отключения клиента
		on_disconnected();
	}

	// Получить буферы
	CNetBuffer *CBaseSocket::recv_buf() const
	{
		return m_recv_buffer;
	}

	CNetBuffer *CBaseSocket::send_buf() const
	{
		return m_send_buffer;
	}

	// Установить издателя
	void CBaseSocket::setSubject(INetSubject *pSubject)
	{
		m_subject = pSubject;
	}

	// Сбросить состояние
	void CBaseSocket::reset()
	{
		// Если сокет не был закрыт, то закрываем его
		if (m_connected)
		{
			evutil_socket_t sock = bufferevent_getfd(m_fd);
			shutdown(sock, SD_BOTH);
			evutil_closesocket(sock);
		}

		m_ip_address = "0.0.0.0";
		m_port = 0;
		m_block_size = 0;
		m_connected = false;
		m_recv_buffer->clear();
		m_send_buffer->clear();

		bufferevent_disable(m_fd, EV_READ | EV_WRITE);
		bufferevent_setfd(m_fd, INVALID_SOCKET);
	}

	// Событие подключения
	void CBaseSocket::on_connected()
	{	
		// Сокет подключен
		m_connected = true;

		// Разрешаем чтение и запись в сокет
		bufferevent_enable(m_fd, EV_READ | EV_WRITE);

		// Говорим пользователю, что мы подключились
		if (m_subject != nullptr) {
			m_subject->notify_connected();
		}
	}

	// Событие отключения
	void CBaseSocket::on_disconnected()
	{
		// Сокет отключен
		m_connected = false;

		// Говорим буферу, что сокет был закрыт
		bufferevent_setfd(m_fd, INVALID_SOCKET);
		bufferevent_disable(m_fd, EV_READ | EV_WRITE);

		// Говорим пользователю, что мы отключились
		if (m_subject != nullptr) {
			m_subject->notify_disconnected();
		}

	}
		
	// Событие получения данных
	void CBaseSocket::on_data_recevied()
	{
		// Временный буфер под данные
		char tmp[128];

		// Размер блока данных
		size_t n = 0;

		// Читаем данные из буфера
		while ( (n = bufferevent_read(m_fd, tmp, sizeof(tmp))) > 0 ) {
			m_recv_buffer->add(tmp, n);
		}

		// Получим размер блока
		if (m_block_size == 0)
		{
			std::memcpy(reinterpret_cast<char *>(&m_block_size), m_recv_buffer->data(), 2);
			m_block_size = htons(m_block_size);
		}

		// Проверим, что размер блока данных не больше размера буфера
		if (m_block_size > m_recv_buffer->size())
		{
			// Отключаем клиента
			close();
			return;
		}

		while (m_recv_buffer->length() >= m_block_size && m_block_size > 0)
		{
			// Обрабатываем пакет
			if (m_subject != nullptr) {
				m_subject->notify_received_data(m_recv_buffer->data(), m_block_size);
			}

			// Удаляем из буфера лишние данные
			m_recv_buffer->remove(m_block_size);

			// Проверяем что в буфере остались данные
			if (m_recv_buffer->length() >= 2)
			{
				std::memcpy(reinterpret_cast<char *>(&m_block_size), m_recv_buffer->data(), 2);
				m_block_size = htons(m_block_size);

				if (m_block_size > m_recv_buffer->size()) {
					close();
					return;
				}
			}
			else {
				// Пакет обработан
				m_block_size = 0;
			}
		}
	}

	// Событие ошибки на сокете
	void CBaseSocket::on_error(int errcode)
	{
		// Говорим пользователю, что произошла ошибка
		if (m_subject != nullptr) {
			m_subject->notify_error(errcode);
		}

		// Закрываем соединение
		close();
	}

	// Сервер
	bool CBaseSocket::is_server() const
	{
		return m_server;
	}
}