#pragma once
#include "INetObserver.h"

namespace PKO
{
	class INetSubject
	{
		public:

			// ������� �����������
			virtual void notify_connected() = 0;

			// ������� ����������
			virtual void notify_disconnected() = 0;

			// ������� ��������� ������
			virtual void notify_received_data(const char *, size_t) = 0;

			// ������� ������
			virtual void notify_error(int errcode) = 0;
	};

	class CNetServerSubject : public INetSubject
	{
		public:

			// �����������
			CNetServerSubject(INetServerObserver *observer) :
				m_observer(observer)
			{

			}

			// ����������
			~CNetServerSubject()
			{

			}
			
			// ������� �����������
			virtual void notify_connected()
			{

			}

			// ������� ����������
			virtual void notify_disconnected()
			{
				m_observer->on_client_disconnected();
			}

			// ������� ��������� ������
			virtual void notify_received_data(const char *data, size_t length)
			{
				m_observer->on_client_recived_data(data, length);
			}

			// ������� ������
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

			// �����������
			CNetClientSubject(INetClientObserver *observer) :
				m_observer(observer)
			{

			}

			// ����������
			~CNetClientSubject()
			{

			}

			// ������� �����������
			virtual void notify_connected()
			{
				m_observer->on_server_connected();
			}

			// ������� ����������
			virtual void notify_disconnected()
			{
				m_observer->on_server_disconnected();
			}

			// ������� ��������� ������
			virtual void notify_received_data(const char *data, size_t length)
			{
				m_observer->on_server_recived_data(data, length);
			}

			// ������� ������
			virtual void notify_error(int errcode)
			{
				m_observer->on_server_error(errcode);
			}

		private:

			INetClientObserver *m_observer;

	};
}

