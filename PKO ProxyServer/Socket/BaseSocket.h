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

			// �����������
			CBaseSocket(event_base *base, size_t recv_buf_size,
								  		  size_t send_buf_size);

			// ����������
			~CBaseSocket();

			// ���������� �����
			void setSocket(evutil_socket_t socket);

			// ���������� IP �����
			void setIpAddress(const std::string& ip_address);

			// ���������� ���� 
			void setPort(unsigned short int port);

			// �������� IP �����
			const std::string& getIpAddress() const;
			
			// �������� ����
			unsigned short int getPort() const;

			// ��������� ������
			void write(const char *data, size_t length);

			// ��������� �� �����
			bool connected() const;

			// ������� ����������
			void close();

			// ���������� ��������
			void setSubject(INetSubject *pSubject);

			// �������� ���������
			void reset();

			// �������� ������
			CNetBuffer *recv_buf() const;
			CNetBuffer *send_buf() const;

			// ������
			bool is_server() const;

		private:

			// ������������� �������
			friend void cb_read(bufferevent *fd, void *arg);
			friend void cb_event(bufferevent *fd, short int what, void *arg);

			// �������� �����������
			CBaseSocket(const CBaseSocket&) = delete;
			CBaseSocket& operator=(const CBaseSocket&) = delete;

		protected:
			// ������� �����������
			virtual void on_connected();

			// ������� ����������
			virtual void on_disconnected();

			// ������� ��������� ������
			virtual void on_data_recevied();

			// ������� ������ �� ������
			virtual void on_error(int errcode);

			// ��������
			INetSubject *m_subject;

			// �����
			bufferevent *m_fd;

			// ����� ��� �������� ������
			CNetBuffer *m_recv_buffer;

			// ����� ��� ��������� ������
			CNetBuffer *m_send_buffer;

			// IP �����
			std::string m_ip_address;

			// ���� 
			unsigned short int m_port;

			// ������ ����� ������
			unsigned short int m_block_size;

			// ��������� �� �����
			bool m_connected;
			
			// ������
			bool m_server;
	};
}



