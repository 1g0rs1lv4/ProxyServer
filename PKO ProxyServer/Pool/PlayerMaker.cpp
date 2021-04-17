#include "PlayerMaker.h"
#include "../Class/Player/Player.h"

namespace PKO
{

	// Конструктор
	CPlayerMaker::CPlayerMaker(CProxyServer *pServer) :
		m_pServer(pServer)
	{

	}

	// Деструктор
	CPlayerMaker::~CPlayerMaker()
	{

	}

	// Создать объект типа CPlayer
	IPoolable *CPlayerMaker::make()
	{
		return new CPlayer(m_pServer);
	}

}