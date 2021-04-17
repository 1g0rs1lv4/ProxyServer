#pragma once
#include "IObjectMaker.h"
#include "../Class/ProxyServer/ProxyServer.h"

namespace PKO
{
	// ��������� �������� ���� CPlayer
	class CPlayerMaker : public IObjectMaker
	{
		public:
			
			// �����������
			CPlayerMaker(CProxyServer *pServer);
			
			// ����������
			~CPlayerMaker();

			// ������� ������ CPlayer
			virtual IPoolable *make();

		private:

			// ��������� �� ���� �������
			CProxyServer *m_pServer;
	};
}


