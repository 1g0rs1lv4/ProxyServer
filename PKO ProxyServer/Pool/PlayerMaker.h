#pragma once
#include "IObjectMaker.h"
#include "../Class/ProxyServer/ProxyServer.h"

namespace PKO
{
	// Создатель объектов типа CPlayer
	class CPlayerMaker : public IObjectMaker
	{
		public:
			
			// Конструктор
			CPlayerMaker(CProxyServer *pServer);
			
			// Деструктор
			~CPlayerMaker();

			// Создать объект CPlayer
			virtual IPoolable *make();

		private:

			// Указатель на ядро событий
			CProxyServer *m_pServer;
	};
}


