#include "ServerSocket.h"

namespace PKO
{

	// �����������
	CServerSocket::CServerSocket(event_base *base, 
			size_t recv_buf_size, size_t send_buf_size) :
		CBaseSocket(base, recv_buf_size, send_buf_size)
	{
		m_server = true;
	}

	// ����������
	CServerSocket::~CServerSocket()
	{

	}

}