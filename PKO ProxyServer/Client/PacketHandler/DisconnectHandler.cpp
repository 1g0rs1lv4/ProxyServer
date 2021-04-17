#include "DisconnectHandler.h"
#include "../../Class/Player/Player.h"
#include <sstream>

namespace PKO
{
	// �����������
	CDisconnectHandler::CDisconnectHandler()
	{

	}

	// ����������
	CDisconnectHandler::~CDisconnectHandler()
	{

	}

	// �������� ID ������
	unsigned short int CDisconnectHandler::getId() const
	{
		return 432;
	}

	// ��������� �����
	void CDisconnectHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// ���������� �����
	bool CDisconnectHandler::handle(CPlayer& Player)
	{
		if (Player.character().stall().installed() && 
			          !Player.character().stall().empty()) {

			return false;

		}

		Player.on_server_logout();

		return true;
	}

	// �������� ����������
	void CDisconnectHandler::reset()
	{

	}

	// �������� ����� �������� ������
	void CDisconnectHandler::after_send(CPlayer& Player) {



	}

}