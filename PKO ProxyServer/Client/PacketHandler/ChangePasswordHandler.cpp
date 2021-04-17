#include "ChangePasswordHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Utils/Utils.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/DisconnectPacket.h"
#include "../../Server/Packet/UpdatePasswordPacket.h"
#include <sstream>

namespace PKO
{
	// �����������
	�ChangePasswordHandler::�ChangePasswordHandler() : szOld(""), szPassword("")
	{
		reset();
	}

	// ����������
	�ChangePasswordHandler::~�ChangePasswordHandler()
	{

	}

	// �������� ID ������
	unsigned short int �ChangePasswordHandler::getId() const
	{
		return 347;
	}

	// ��������� �����
	void �ChangePasswordHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		szOld = Reader.readString();
		szPassword = Reader.readString();
	}

	// ���������� �����
	bool �ChangePasswordHandler::handle(CPlayer& Player)
	{
		// ��������� ���������� ������
		if (!PKO::CUtils::IsValidSecretPassword(szPassword))
		{
			std::stringstream message;
			message << "bad secret password \"" << szPassword << "\"";
			Player.sendDebug(message.str());

			// �������� ������
			CUpdatePasswordPacket password_packet;
			Player.sendPacket(Player.server(), &password_packet);

			return false;
		}
		return true;
	}

	// �������� ����������
	void �ChangePasswordHandler::reset()
	{
		szOld = "";
		szPassword = "";
	}

	// �������� ����� �������� ������
	void �ChangePasswordHandler::after_send(CPlayer& Player) {



	}

}