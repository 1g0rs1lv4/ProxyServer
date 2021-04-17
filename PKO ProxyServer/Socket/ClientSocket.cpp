#include <iostream>
#include "ClientSocket.h"
#include "callback.h"

namespace PKO
{
	CClientSocket::CClientSocket(event_base *base, 
				size_t recv_buf_size, size_t send_buf_size) :
		CBaseSocket(base, recv_buf_size, send_buf_size)
	{
		m_server = false;
	}

	CClientSocket::~CClientSocket()
	{

	}

	// ������������ � �������
	void CClientSocket::open()
	{
		// ��������� ������ �������
		sockaddr_in serveraddr;
		std::memset(&serveraddr, 0x00, sizeof(serveraddr));

		// ��������� ��������� ������ �������
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip_address.c_str(), &serveraddr.sin_addr);
	
		// ������������ � �������
		bufferevent_socket_connect(m_fd, reinterpret_cast<const sockaddr *>(&serveraddr), sizeof(serveraddr));
		
	}

}
