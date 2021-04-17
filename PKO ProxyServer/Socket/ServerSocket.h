#pragma once
#include "BaseSocket.h"

namespace PKO
{
	class CServerSocket : public CBaseSocket
	{
		public:

			// �����������
			CServerSocket(event_base *base, size_t recv_buf_size,
											size_t send_buf_size);

			// ����������
			virtual ~CServerSocket();

		private:

			// �������� �����������
			CServerSocket(const CServerSocket&) = delete;
			CServerSocket& operator=(const CServerSocket&) = delete;
	};

}

