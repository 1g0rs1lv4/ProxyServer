#include "SysInfoHandler.h"
#include "../../Class/Player/Player.h"
#include "../../Binary/BinaryReader.h"
#include "../../Server/Packet/GMNoticePacket.h"

namespace PKO
{

	// �����������
	CSysInfoHandler::CSysInfoHandler() :
		m_message("")
	{

	}

	// ����������
	CSysInfoHandler::~CSysInfoHandler()
	{

	}

	// �������� ID ������
	unsigned short int CSysInfoHandler::getId() const
	{
		return 517;
	}

	// ��������� �����
	void CSysInfoHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_message = Reader.readString();
	}

	// ���������� �����
	bool CSysInfoHandler::handle(CPlayer& Player)
	{
		
		// ���������� ����
		bool found = false;
		std::string message;
		std::string filter = "��� ��� ������������";
		size_t pos = m_message.find(filter);
		if (pos != std::string::npos)
		{
			message = "��� ������ " + Player.character().getName() + " ������������ " + m_message.substr(filter.length(), m_message.length() - filter.length());
			found = true;
		}
		else
		{
			filter = "������������ ��� ���";
			pos = m_message.find(filter);
			if (pos != std::string::npos) {
				message = m_message.substr(0, pos - 1) + " ������������ ��� ������ " + Player.character().getName() + m_message.substr(pos + filter.length(), m_message.length() - filter.length());
				found = true;
			}
		}

		filter = "�������������";
		pos = m_message.find(filter);
		if (pos != std::string::npos)
		{
			message = m_message.substr(0, pos - 1) + " ������������� ��� ������ " + Player.character().getName() + "!";
			found = true;
		}

		if (found)
		{
			CGMNoticePacket notice_packet;
			notice_packet.setMessage(message);

			const player_list_t& players = Player.stall_server()->getPlayers();
			auto i = players.begin();
			while (i != players.end())
			{
				CPlayer *ply = *i;
				if (ply->server()->connected()) {
					ply->sendPacket(ply->server(), &notice_packet);
				}

				i++;
			}
		}

		return true;
	}

	// �������� ����������
	void CSysInfoHandler::reset()
	{
		m_message = "";
	}
}