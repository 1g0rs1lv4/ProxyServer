#include "ChangePasswordHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Utils/Utils.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/DisconnectPacket.h"
#include "../../Server/Packet/UpdatePasswordPacket.h"
#include <sstream>

namespace PKO
{
	// Êîíñòğóêòîğ
	ÑChangePasswordHandler::ÑChangePasswordHandler() : szOld(""), szPassword("")
	{
		reset();
	}

	// Äåñòğóêòîğ
	ÑChangePasswordHandler::~ÑChangePasswordHandler()
	{

	}

	// Ïîëó÷èòü ID ïàêåòà
	unsigned short int ÑChangePasswordHandler::getId() const
	{
		return 347;
	}

	// Ïğî÷èòàòü ïàêåò
	void ÑChangePasswordHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		szOld = Reader.readString();
		szPassword = Reader.readString();
	}

	// Îáğàáîòàòü ïàêåò
	bool ÑChangePasswordHandler::handle(CPlayer& Player)
	{
		// Ïğîâåğÿåì âàëèäíîñòü ïàğîëÿ
		if (!PKO::CUtils::IsValidSecretPassword(szPassword))
		{
			std::stringstream message;
			message << "bad secret password \"" << szPassword << "\"";
			Player.sendDebug(message.str());

			// Ïîñûëàåì îøèáêó
			CUpdatePasswordPacket password_packet;
			Player.sendPacket(Player.server(), &password_packet);

			return false;
		}
		return true;
	}

	// Ñáğîñèòü îáğàáîò÷èê
	void ÑChangePasswordHandler::reset()
	{
		szOld = "";
		szPassword = "";
	}

	// Äåéñòâèå ïîñëå îòïğàâêè ïàêåòà
	void ÑChangePasswordHandler::after_send(CPlayer& Player) {



	}

}