#include "BeginSeeHandler.h"
#include "../../Class/Player/Player.h"


#define MonsterDiapazon 0xb0000000

namespace PKO
{
	// �����������
	CBeginSeeHandler::CBeginSeeHandler()
		: cha_id(0), model_id(0), findPlayer(NULL)
	{

	}

	// ����������
	CBeginSeeHandler::~CBeginSeeHandler()
	{

	}

	// �������� ID ������
	unsigned short int CBeginSeeHandler::getId() const
	{
		return 504;
	}

	// ��������� �����
	void CBeginSeeHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

		// ���������� ����
		Reader.seek(1, PKO::seek_cur);

		// ������� id ������
		model_id = (int) Reader.readUint32();
		// ������� id ���������
		cha_id = (int)Reader.readUint32();

		// ��������, ��� �������� �� ������
		if (cha_id < MonsterDiapazon) {

			// ���� ������
			findPlayer = Player.stall_server()->FindPlayerByID(cha_id);

		}
		
	}

	// ���������� �����
	bool CBeginSeeHandler::handle(CPlayer& Player)
	{

		return true;

	}

	// �������� ����������
	void CBeginSeeHandler::reset()
	{
		cha_id = 0;
		model_id = 0;
		findPlayer = NULL;
	}

	// �������� ����� �������� ������
	void CBeginSeeHandler::after_send(CPlayer& Player) {

		// ����� ������
		if (findPlayer) {

			// ���������� �� �����
			if (findPlayer->character().stall().installed()) {

				// ������ �����
				if (!findPlayer->server()->connected()) {

					// ������� ����� � �������������� ���
					//CStallColorPacket stallColor(cha_id, 0xFFFF0000);
					// ���������� �����
					//Player.sendPacket(Player.server(), &stallColor);

				} else {

					// ������� ����� � �������������� ���
					//CStallColorPacket stallColor(cha_id, 0xFF008000);
					// ���������� �����
					//Player.sendPacket(Player.server(), &stallColor);

				}

			}

		}

	}

}