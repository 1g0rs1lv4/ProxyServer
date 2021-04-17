#pragma once

namespace PKO
{
	class INetObserver
	{

	};


	class INetServerObserver : public INetObserver
	{
		public:
			
			virtual void on_client_disconnected() = 0;
			virtual void on_client_recived_data(const char *, size_t) = 0;
			virtual void on_client_error(int) = 0;
	};

	class INetClientObserver : public INetObserver
	{
		public:
			virtual void on_server_connected() = 0;
			virtual void on_server_disconnected() = 0;
			virtual void on_server_recived_data(const char *, size_t) = 0;
			virtual void on_server_error(int) = 0;
	};
}

