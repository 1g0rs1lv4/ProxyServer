#include <event2\event.h>
#include <event2\buffer.h>
#include "BaseSocket.h"
#include "callback.h"

namespace PKO
{
	// �����������
	CBaseSocket::CBaseSocket(event_base *base, 
					size_t recv_buf_size, size_t send_buf_size)
	{
		// ������� �����
		m_fd = bufferevent_socket_new(base, INVALID_SOCKET, BEV_OPT_CLOSE_ON_FREE);
		bufferevent_setwatermark(m_fd, EV_READ | EV_WRITE, 2, 0);
		bufferevent_setcb(m_fd, cb_read, NULL, cb_event, this);
		
		// ������� ������ ��� �������� � ��������� ������
		m_recv_buffer = new CNetBuffer(recv_buf_size);
		m_send_buffer = new CNetBuffer(send_buf_size);

		// �������������� ������ �����
		m_block_size = 0;

		// ����� ��������
		m_connected = false;

		// ������ 
		m_server = false;
	}

	// ����������
	CBaseSocket::~CBaseSocket()
	{
		// ������� �������� 
		if (m_subject != nullptr) {
			delete m_subject;
		}

		// ������� ������
		delete m_send_buffer;
		delete m_recv_buffer;

		// ������� �����
		bufferevent_free(m_fd);
	}

	// ���������� �����
	void CBaseSocket::setSocket(evutil_socket_t socket)
	{
		m_connected = true;
		bufferevent_setfd(m_fd, socket);
		bufferevent_enable(m_fd, EV_READ | EV_WRITE);
	}

	// ���������� IP �����
	void CBaseSocket::setIpAddress(const std::string& ip_address)
	{
		m_ip_address = ip_address;
	}

	// ���������� ���� 
	void CBaseSocket::setPort(unsigned short int port)
	{
		m_port = port;
	}

	// �������� IP �����
	const std::string& CBaseSocket::getIpAddress() const
	{
		return m_ip_address;
	}

	// �������� ����
	unsigned short int CBaseSocket::getPort() const
	{
		return m_port;
	}

	// ��������� ������
	void CBaseSocket::write(const char *data, size_t length)
	{
		bufferevent_write(m_fd, data, length);
	}

	// ��������� �� �����
	bool CBaseSocket::connected() const
	{
		return m_connected;
	}

	// ������� ����������
	void CBaseSocket::close()
	{
		// ��������, ��� ����� ���������
		if (!m_connected) {
			return;
		}

		evutil_socket_t sock = bufferevent_getfd(m_fd);

		// ��������� ����������
		shutdown(sock, SD_BOTH);

		// ��������� �����
		evutil_closesocket(sock);

		// �������� ������� ���������� �������
		on_disconnected();
	}

	// �������� ������
	CNetBuffer *CBaseSocket::recv_buf() const
	{
		return m_recv_buffer;
	}

	CNetBuffer *CBaseSocket::send_buf() const
	{
		return m_send_buffer;
	}

	// ���������� ��������
	void CBaseSocket::setSubject(INetSubject *pSubject)
	{
		m_subject = pSubject;
	}

	// �������� ���������
	void CBaseSocket::reset()
	{
		// ���� ����� �� ��� ������, �� ��������� ���
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

	// ������� �����������
	void CBaseSocket::on_connected()
	{	
		// ����� ���������
		m_connected = true;

		// ��������� ������ � ������ � �����
		bufferevent_enable(m_fd, EV_READ | EV_WRITE);

		// ������� ������������, ��� �� ������������
		if (m_subject != nullptr) {
			m_subject->notify_connected();
		}
	}

	// ������� ����������
	void CBaseSocket::on_disconnected()
	{
		// ����� ��������
		m_connected = false;

		// ������� ������, ��� ����� ��� ������
		bufferevent_setfd(m_fd, INVALID_SOCKET);
		bufferevent_disable(m_fd, EV_READ | EV_WRITE);

		// ������� ������������, ��� �� �����������
		if (m_subject != nullptr) {
			m_subject->notify_disconnected();
		}

	}
		
	// ������� ��������� ������
	void CBaseSocket::on_data_recevied()
	{
		// ��������� ����� ��� ������
		char tmp[128];

		// ������ ����� ������
		size_t n = 0;

		// ������ ������ �� ������
		while ( (n = bufferevent_read(m_fd, tmp, sizeof(tmp))) > 0 ) {
			m_recv_buffer->add(tmp, n);
		}

		// ������� ������ �����
		if (m_block_size == 0)
		{
			std::memcpy(reinterpret_cast<char *>(&m_block_size), m_recv_buffer->data(), 2);
			m_block_size = htons(m_block_size);
		}

		// ��������, ��� ������ ����� ������ �� ������ ������� ������
		if (m_block_size > m_recv_buffer->size())
		{
			// ��������� �������
			close();
			return;
		}

		while (m_recv_buffer->length() >= m_block_size && m_block_size > 0)
		{
			// ������������ �����
			if (m_subject != nullptr) {
				m_subject->notify_received_data(m_recv_buffer->data(), m_block_size);
			}

			// ������� �� ������ ������ ������
			m_recv_buffer->remove(m_block_size);

			// ��������� ��� � ������ �������� ������
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
				// ����� ���������
				m_block_size = 0;
			}
		}
	}

	// ������� ������ �� ������
	void CBaseSocket::on_error(int errcode)
	{
		// ������� ������������, ��� ��������� ������
		if (m_subject != nullptr) {
			m_subject->notify_error(errcode);
		}

		// ��������� ����������
		close();
	}

	// ������
	bool CBaseSocket::is_server() const
	{
		return m_server;
	}
}