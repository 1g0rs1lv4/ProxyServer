#include "AccountLoginHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include "../../Class/Utils/Utils.h"
#include "../Packet/DisconnectPacket.h"
#include "../../Server/Packet/WrongLoginPacket.h"
#include "../../Server/Packet/WrongVersionPacket.h"
#include "../Packet/LoginPacket.h"
#include <sstream>
#include <iostream>

namespace PKO
{
	// �����������
	CAccountLoginHandler::CAccountLoginHandler() : m_nobill(""), m_login(""), m_password(""), m_mac(""),
		m_flag(0), m_version(0)
	{

	}

	// ����������
	CAccountLoginHandler::~CAccountLoginHandler()
	{

	}

	// �������� ID ������
	unsigned short int CAccountLoginHandler::getId() const
	{
		return 431;
	}

	// ��������� �����

	void CAccountLoginHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_nobill = Reader.readString();
		m_login = Reader.readString();
		m_password = Reader.readString();
		m_mac = Reader.readString();
		m_flag = Reader.readUint16();
		m_version = Reader.readUint16();
		p_version_1 = Reader.readByte();
		p_version_2 = Reader.readByte();

	}

	// ���������� �����
	bool CAccountLoginHandler::handle(CPlayer& Player)
	{

		unsigned short protectVer = Player.protection().getVersion();

		// �������� ������ ������
		if (protectVer) {

			if (p_version_1 != HIBYTE(protectVer) || p_version_2 != LOBYTE(protectVer)) {

				// �������� ������ - ��������� �� �������
				CWrongVersionPacket wrong_version_packet;
				Player.sendPacket(Player.server(), &wrong_version_packet);

				// ��������� ���������� ����������
				CDisconnectPacket disconnect_packet(Player, "Protection");
				Player.sendPacket(Player.client(), &disconnect_packet);

				return false;

			}

		}

		// ���������� ������ ��������
		Player.account().setLogin(m_login);
		Player.account().setPassword(m_password);
		Player.account().setMacAddress(m_mac);
		Player.account().setBillString(m_nobill);
		Player.account().setMacAddress(m_mac);
		Player.account().setFlag(m_flag);
		Player.account().setVersion(m_version);

		// ��������� ���������� MAC ������
		if (!PKO::CUtils::IsValidMac(m_mac))
		{
			std::stringstream message;
			message << "Wrong MAC Adress \"" << m_mac << "\"";
			Player.sendDebug(message.str());

			// ����������� �� �������
			CWrongLoginPacket wronglogin_packet;
			Player.sendPacket(Player.server(), &wronglogin_packet);

			CDisconnectPacket disconnect_packet(Player, "Wrong MAC Adress");
			Player.sendPacket(Player.client(), &disconnect_packet);
			return false;
		}

		// ��������� ������ � ������
		// ������� ������ �������
		const player_list_t& players = Player.stall_server()->getPlayers();

		// ���� ������ � ����� �� ���������
		auto i = players.begin();
		while (i != players.end())
		{
			CPlayer *pOnlinePlayer = (*i);
			if (pOnlinePlayer == &Player)
			{
				i++;
				continue;
			}

			if (CUtils::LowerCase(pOnlinePlayer->account().getLogin()) == CUtils::LowerCase(Player.account().getLogin()) 
				// ������ ������
				&& pOnlinePlayer->account().getPassword() == Player.account().getPassword()
			)
			{
				if (pOnlinePlayer->character().stall().installed() &&
							!pOnlinePlayer->server()->connected() )
				{

					// ����������� �� �������
					CDisconnectPacket disconnect_packet(Player, "Relogin");
					pOnlinePlayer->sendPacket(pOnlinePlayer->client(), &disconnect_packet);
					
					// ������� �� �������
					Player.do_relogin();

					return false;
				}

				break;
			}

			i++;
		}

		// ������� ����� �����
		CLoginPacket login_packet;
		login_packet.setChapString(Player.account().getChapString());
		login_packet.setNobill(m_nobill);
		login_packet.setLogin(m_login);
		login_packet.setPassword(m_password);
		login_packet.setMacAddress(m_mac);
		login_packet.setIpAddress(Player.server()->getIpAddress());
		login_packet.setFlag(m_flag);
		login_packet.setVersion(m_version);
		
		// ���������� ����� ����� �� ������
		Player.sendPacket(Player.client(), &login_packet);
		return false;
	}

	// �������� ����������
	void CAccountLoginHandler::reset()
	{
		m_nobill = "";
		m_login = "";
		m_password = "";
		m_mac = "";
		m_flag = 0;
		m_version = 0;
	}

	// �������� ����� �������� ������
	void CAccountLoginHandler::after_send(CPlayer& Player) {



	}

}