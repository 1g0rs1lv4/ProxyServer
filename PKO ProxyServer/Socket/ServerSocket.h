#pragma once
#include "BaseSocket.h"

namespace PKO
{
	class CServerSocket : public CBaseSocket
	{
		public:

			// Конструктор
			CServerSocket(event_base *base, size_t recv_buf_size,
											size_t send_buf_size);

			// Деструктор
			virtual ~CServerSocket();

		private:

			// Запретим копирование
			CServerSocket(const CServerSocket&) = delete;
			CServerSocket& operator=(const CServerSocket&) = delete;
	};

}

