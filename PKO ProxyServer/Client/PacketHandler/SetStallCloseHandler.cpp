#include "SetStallCloseHandler.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// �����������
	CSetStallCloseHandler::CSetStallCloseHandler()
	{

	}

	// ����������
	CSetStallCloseHandler::~CSetStallCloseHandler()
	{

	}

	// �������� ID ������
	unsigned short int CSetStallCloseHandler::getId() const
	{
		return 333;
	}

	// ��������� �����
	void CSetStallCloseHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// ���������� �����
	bool CSetStallCloseHandler::handle(CPlayer& Player)
	{
		// ������� �����
		Player.character().stall().init();

		return true;
	}

	// �������� ����������
	void CSetStallCloseHandler::reset()
	{

	}

	// �������� ����� �������� ������
	void CSetStallCloseHandler::after_send(CPlayer& Player) {



	}

}