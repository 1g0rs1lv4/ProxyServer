#include "GMNoticeHandler.h"
#include "../Packet/GMNoticePacket.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// �����������
	CGMNotice::CGMNotice()
		: m_message("")
	{

	}

	// ����������
	CGMNotice::~CGMNotice()
	{

	}

	// �������� ID ������
	unsigned short int CGMNotice::getId() const
	{
		return 780;
	}

	// ��������� �����
	void CGMNotice::read(CBinaryReader& Reader, CPlayer& Player)
	{
		// ������� ���������� �� ���������
		m_message = Reader.readString();
	}

	// ���������� �����
	bool CGMNotice::handle(CPlayer& Player)
	{
		
		// ���������� ����� �� ��������� ��� �������
		CGMNoticePacket notice_packet;
		notice_packet.setMessage(m_message);

		// �������� ���� �� ���������
		const player_list_t& players = Player.stall_server()->getPlayers();
		auto i = players.begin();
		while (i != players.end())
		{
			CPlayer* ply = *i;
			if (ply->server()->connected()) {
				ply->sendPacket(ply->server(), &notice_packet);
			}

			i++;
		}

		return true;
	}

	// �������� ����������
	void CGMNotice::reset()
	{

	}

	// �������� ����� �������� ������
	void CGMNotice::after_send(CPlayer& Player) {



	}

}