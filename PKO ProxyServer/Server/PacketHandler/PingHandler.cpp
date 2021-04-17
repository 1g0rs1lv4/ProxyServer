#include "PingHandler.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/PingPacket.h"

namespace PKO
{
	// �����������
	CPingHandler::CPingHandler()
	{

	}

	// ����������
	CPingHandler::~CPingHandler()
	{

	}

	// �������� ID ������
	unsigned short int CPingHandler::getId() const
	{
		return 537;
	}

	// ��������� �����
	void CPingHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// ���������� �����
	bool CPingHandler::handle(CPlayer& Player)
	{
		// ���������� ������� ���� ������
		if (!Player.server()->connected())
		{
			CPingPacket ping_packet;
			Player.sendPacket(Player.client(), &ping_packet);

			return false;
		}

		return true;
	}

	// �������� ����������
	void CPingHandler::reset()
	{

	}

	// �������� ����� �������� ������
	void CPingHandler::after_send(CPlayer& Player) {



	}

}