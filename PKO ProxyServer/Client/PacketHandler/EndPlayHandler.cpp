#include "EndPlayHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <iostream>

namespace PKO
{
	// �����������
	CEndPlayHandler::CEndPlayHandler()
	{

	}

	// ����������
	CEndPlayHandler::~CEndPlayHandler()
	{

	}

	// �������� ID ������
	unsigned short int CEndPlayHandler::getId() const
	{
		return 434;
	}


	// ��������� ����� 
	void CEndPlayHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// ���������� �����
	bool CEndPlayHandler::handle(CPlayer& Player)
	{

		/*PKO::CSetStall playerStall = Player.character().stall();

		// ���� ���������� �����
		if (playerStall.installed()) {

			// ������� �����
			playerStall.setInstalled(false);
			playerStall.setCellCount(0);

		}

		*/
		
		return true;

	}

	// �������� ����������
	void CEndPlayHandler::reset()
	{
		
	}

	// �������� ����� �������� ������
	void CEndPlayHandler::after_send(CPlayer& Player) {



	}

}