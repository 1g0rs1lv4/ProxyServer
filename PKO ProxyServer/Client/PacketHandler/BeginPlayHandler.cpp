#include "BeginPlayHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <iostream>

namespace PKO
{
	// �����������
	CBeginPlayHandler::CBeginPlayHandler()
	{

	}

	// ����������
	CBeginPlayHandler::~CBeginPlayHandler()
	{

	}

	// �������� ID ������
	unsigned short int CBeginPlayHandler::getId() const
	{

		return 433;

	}


	// ��������� ����� 
	void CBeginPlayHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

		// ������� ���������� ���������
		selectCha = Reader.readString();

	}

	// ���������� �����
	bool CBeginPlayHandler::handle(CPlayer& Player)
	{

		return true;

	}

	// �������� ����������
	void CBeginPlayHandler::reset()
	{

	}

	// �������� ����� �������� ������
	void CBeginPlayHandler::after_send(CPlayer& Player) {



	}
}