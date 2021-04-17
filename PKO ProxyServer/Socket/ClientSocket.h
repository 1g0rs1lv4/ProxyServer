#pragma once
#include <string>
#include <event2\bufferevent.h>
#include "BaseSocket.h"

namespace PKO
{
	// Сокет клиента
	class CClientSocket : public CBaseSocket
	{
		public:

			// Конструктор
			CClientSocket(event_base *base, size_t recv_buf_size,
											size_t send_buf_size);

			// Деструктор
			virtual ~CClientSocket();

			// Подключиться к серверу
			void open();

		private:

			// Запретим копирование
			CClientSocket(const CClientSocket&) = delete;
			CClientSocket& operator=(const CClientSocket&) = delete;
	};


}
