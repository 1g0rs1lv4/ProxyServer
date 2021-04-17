#pragma once
#include <event2\bufferevent.h>

namespace PKO
{
	// Интерфейс сокета
	class ISocket
	{
		public:
			
			// Событие подключения
			virtual void on_connected() = 0;

			// Событие отключения
			virtual void on_disconnected() = 0;

			// Событие получения данных
			virtual void on_data_recevied() = 0;

			// Событие ошибки на сокете
			virtual void on_error(int) = 0;
	};

}
