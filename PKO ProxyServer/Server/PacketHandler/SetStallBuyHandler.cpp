#include "SetStallBuyHandler.h"
#include "../../Class/Player/Player.h"
#include "../../Binary/BinaryReader.h"
#include "../../Client/Packet/DisconnectPacket.h"

namespace PKO
{
	// �����������
	CSetStallBuyHandler::CSetStallBuyHandler() :
		m_cha_id(0), m_grid_id(0), m_item_count(0)
	{

	}

	// ����������
	CSetStallBuyHandler::~CSetStallBuyHandler()
	{

	}

	// �������� ID ������
	unsigned short int CSetStallBuyHandler::getId() const
	{
		return 856;
	}

	// ��������� �����
	void CSetStallBuyHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		// ������ ID ���������
		m_cha_id = Reader.readUint32();
		
		// ������ ID ������
		m_grid_id = static_cast<unsigned int>(Reader.readByte());
		
		// ������ ���������� ���������
		m_item_count = static_cast<unsigned int>(Reader.readByte());
	}

	// ���������� �����
	bool CSetStallBuyHandler::handle(CPlayer& Player)
	{
		if (Player.character().getId() == m_cha_id)
		{
			if (Player.character().stall().installed())
			{
				// ��������� ���������� ��������� � ������
				Player.character().stall().updateCell(m_grid_id, m_item_count);

				// ��������� ������, ���� ����� ����
				if (Player.stall_server()->config().auto_close_on_empty())
				{
					if (Player.character().stall().empty() &&
						!Player.server()->connected())
					{
						CDisconnectPacket disconnect_packet(Player, "Empty stall.");
						Player.sendPacket(Player.client(), &disconnect_packet);
						return false;
					}
				}
			}
		}

		return true;
	}

	// �������� ����������
	void CSetStallBuyHandler::reset()
	{
		m_cha_id = 0;
		m_grid_id = 0;
		m_item_count = 0;
	}

	// �������� ����� �������� ������
	void CSetStallBuyHandler::after_send(CPlayer& Player) {



	}

}
