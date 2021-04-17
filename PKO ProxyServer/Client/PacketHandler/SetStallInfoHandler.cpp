#include "SetStallInfoHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include "../../Server/Packet/PopupNoticePacket.h"
#include "../../Class/Utils/Utils.h"

namespace PKO
{
	// �����������
	CSetStallInfoHandler::CSetStallInfoHandler()
	{
		reset();
	}

	// ����������
	CSetStallInfoHandler::~CSetStallInfoHandler()
	{

	}

	// �������� ID ������
	unsigned short int CSetStallInfoHandler::getId() const
	{
		return 330;
	}

	// ��������� �����
	void CSetStallInfoHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		// ������ �������� ������
		m_name = Reader.readString();
		
		// ������ ���������� �����
		m_slot_number = static_cast<unsigned short int>(Reader.readByte());
		
		// ������ ������
		for (unsigned short int i = 0; i < m_slot_number; i++)
		{
			m_cells[i].grid = Reader.readByte();
			m_cells[i].money = Reader.readUint32();
			m_cells[i].count = Reader.readByte();
			m_cells[i].index = Reader.readByte();
		}
	}

	// ���������� �����
	bool CSetStallInfoHandler::handle(CPlayer& Player)
	{

		// ������������� �������� ������
		Player.character().stall().setName(m_name);

		// ������������� ���������� �����
		Player.character().stall().setCellCount(m_slot_number);

		// ������������� ������ ������
		for (unsigned int i = 0; i < MAX_CELL_NUM; i++) {
			Player.character().stall().setCell(m_cells[i]);
		}

		return true;
	}

	// �������� ����������
	void CSetStallInfoHandler::reset()
	{
		m_name = "";
		m_slot_number = 0;

		for (unsigned int i = 0; i < MAX_CELL_NUM; i++) 
		{
			m_cells[i].grid = 0;
			m_cells[i].money = 0;
			m_cells[i].count = 0;
			m_cells[i].index = 0;
		}
	}

	// �������� ����� �������� ������
	void CSetStallInfoHandler::after_send(CPlayer& Player) {



	}

}