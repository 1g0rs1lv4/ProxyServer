#include "DisconnectPacket.h"
#include <iostream>
#include <string>
#include <sstream>

namespace PKO
{
	// �����������
	CDisconnectPacket::CDisconnectPacket(CPlayer& Player, const std::string reason)
	{
		try
		{
			/*std::stringstream message;
			message << "[connection] Client (0x" << this << ")" << Player.server()->getIpAddress() << " Disconnect client. Reason: [" << reason << "]";
			Player.stall_server()->sendDebug(message.str());*/
		}
		catch (...)
		{

		}
	}

	// ����������
	CDisconnectPacket::~CDisconnectPacket()
	{

	}

	// �������� ID ������
	unsigned short int CDisconnectPacket::getId() const
	{
		return 432;
	}

	// �������� ����� � �����
	void CDisconnectPacket::write(CBinaryWriter& Writer)
	{

	}
}