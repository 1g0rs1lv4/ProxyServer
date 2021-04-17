#include "DisconnectPacket.h"
#include <iostream>
#include <string>
#include <sstream>

namespace PKO
{
	// Конструктор
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

	// Деструктор
	CDisconnectPacket::~CDisconnectPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CDisconnectPacket::getId() const
	{
		return 432;
	}

	// Записать пакет в буфер
	void CDisconnectPacket::write(CBinaryWriter& Writer)
	{

	}
}