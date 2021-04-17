#pragma once
#include <event2\bufferevent.h>

namespace PKO
{
	// ��������� ������
	class ISocket
	{
		public:
			
			// ������� �����������
			virtual void on_connected() = 0;

			// ������� ����������
			virtual void on_disconnected() = 0;

			// ������� ��������� ������
			virtual void on_data_recevied() = 0;

			// ������� ������ �� ������
			virtual void on_error(int) = 0;
	};

}
