#pragma once
#include <string>
#include "ISocket.h"
#include "INetSubject.h"
#include "NetBuffer.h"

namespace PKO
{

	class CBaseSocket : public ISocket
	{
		public:

			// Конструктор
			CBaseSocket(event_base *base, size_t recv_buf_size,
								  		  size_t send_buf_size);

			// Деструктор
			~CBaseSocket();

			// Установить сокет
			void setSocket(evutil_socket_t socket);

			// Установить IP адрес
			void setIpAddress(const std::string& ip_address);

			// Установить порт 
			void setPort(unsigned short int port);

			// Получить IP адрес
			const std::string& getIpAddress() const;
			
			// Получить порт
			unsigned short int getPort() const;

			// Отправить данные
			void write(const char *data, size_t length);

			// Подключен ли сокет
			bool connected() const;

			// Закрыть соединение
			void close();

			// Установить издателя
			void setSubject(INetSubject *pSubject);

			// Сбросить состояние
			void reset();

			// Получить буферы
			CNetBuffer *recv_buf() const;
			CNetBuffer *send_buf() const;

			// Сервер
			bool is_server() const;

		private:

			// Дружественные функции
			friend void cb_read(bufferevent *fd, void *arg);
			friend void cb_event(bufferevent *fd, short int what, void *arg);

			// Запретим копирование
			CBaseSocket(const CBaseSocket&) = delete;
			CBaseSocket& operator=(const CBaseSocket&) = delete;

		protected:
			// Событие подключения
			virtual void on_connected();

			// Событие отключения
			virtual void on_disconnected();

			// Событие получения данных
			virtual void on_data_recevied();

			// Событие ошибки на сокете
			virtual void on_error(int errcode);

			// Издатель
			INetSubject *m_subject;

			// Сокет
			bufferevent *m_fd;

			// Буфер для входящих данных
			CNetBuffer *m_recv_buffer;

			// Буфер для исходящих данных
			CNetBuffer *m_send_buffer;

			// IP адрес
			std::string m_ip_address;

			// Порт 
			unsigned short int m_port;

			// Размер блока данных
			unsigned short int m_block_size;

			// Подключен ли сокет
			bool m_connected;
			
			// Сервер
			bool m_server;
	};
}



