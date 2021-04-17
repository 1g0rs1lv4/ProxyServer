#pragma once
#include <string>
#include <event2\bufferevent.h>
#include "BaseSocket.h"

namespace PKO
{
	// ����� �������
	class CClientSocket : public CBaseSocket
	{
		public:

			// �����������
			CClientSocket(event_base *base, size_t recv_buf_size,
											size_t send_buf_size);

			// ����������
			virtual ~CClientSocket();

			// ������������ � �������
			void open();

		private:

			// �������� �����������
			CClientSocket(const CClientSocket&) = delete;
			CClientSocket& operator=(const CClientSocket&) = delete;
	};


}
