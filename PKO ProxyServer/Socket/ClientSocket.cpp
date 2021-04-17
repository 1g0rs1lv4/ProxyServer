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

	// Подключиться к серверу
	void CClientSocket::open()
	{
		// Структура адреса сервера
		sockaddr_in serveraddr;
		std::memset(&serveraddr, 0x00, sizeof(serveraddr));

		// Заполняем структуру адреса сервера
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(m_port);
		inet_pton(AF_INET, m_ip_address.c_str(), &serveraddr.sin_addr);
	
		// Подключаемся к серверу
		bufferevent_socket_connect(m_fd, reinterpret_cast<const sockaddr *>(&serveraddr), sizeof(serveraddr));
		
	}

}
