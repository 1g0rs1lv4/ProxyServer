#pragma once
#include "INetObserver.h"

namespace PKO
{
	class INetSubject
	{
		public:

			// Событие подключения
			virtual void notify_connected() = 0;

			// Событие отключения
			virtual void notify_disconnected() = 0;

			// Событие получения данных
			virtual void notify_received_data(const char *, size_t) = 0;

			// Событие ошибки
			virtual void notify_error(int errcode) = 0;
	};

	class CNetServerSubject : public INetSubject
	{
		public:

			// Конструктор
			CNetServerSubject(INetServerObserver *observer) :
				m_observer(observer)
			{

			}

			// Деструктор
			~CNetServerSubject()
			{

			}
			
			// Событие подключения
			virtual void notify_connected()
			{

			}

			// Событие отключения
			virtual void notify_disconnected()
			{
				m_observer->on_client_disconnected();
			}

			// Событие получения данных
			virtual void notify_received_data(const char *data, size_t length)
			{
				m_observer->on_client_recived_data(data, length);
			}

			// Событие ошибки
			virtual void notify_error(int errcode)
			{
				m_observer->on_client_error(errcode);
			}

		private:

			INetServerObserver *m_observer;
	};

	class CNetClientSubject : public INetSubject
	{
		public:

			// Конструктор
			CNetClientSubject(INetClientObserver *observer) :
				m_observer(observer)
			{

			}

			// Деструктор
			~CNetClientSubject()
			{

			}

			// Событие подключения
			virtual void notify_connected()
			{
				m_observer->on_server_connected();
			}

			// Событие отключения
			virtual void notify_disconnected()
			{
				m_observer->on_server_disconnected();
			}

			// Событие получения данных
			virtual void notify_received_data(const char *data, size_t length)
			{
				m_observer->on_server_recived_data(data, length);
			}

			// Событие ошибки
			virtual void notify_error(int errcode)
			{
				m_observer->on_server_error(errcode);
			}

		private:

			INetClientObserver *m_observer;

	};
}

