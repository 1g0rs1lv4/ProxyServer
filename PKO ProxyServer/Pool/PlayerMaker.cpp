#include "PlayerMaker.h"
#include "../Class/Player/Player.h"

namespace PKO
{

	// �����������
	CPlayerMaker::CPlayerMaker(CProxyServer *pServer) :
		m_pServer(pServer)
	{

	}

	// ����������
	CPlayerMaker::~CPlayerMaker()
	{

	}

	// ������� ������ ���� CPlayer
	IPoolable *CPlayerMaker::make()
	{
		return new CPlayer(m_pServer);
	}

}