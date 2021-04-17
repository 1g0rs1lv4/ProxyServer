#include "CreatePasswordHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Utils/Utils.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/DisconnectPacket.h"
#include "../../Server/Packet/CreatePasswordPacket.h"
#include <sstream>

namespace PKO
{
	// Конструктор
	CCreatePasswordHandler::CCreatePasswordHandler() : szPassword("")
	{
		reset();
	}

	// Деструктор
	CCreatePasswordHandler::~CCreatePasswordHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CCreatePasswordHandler::getId() const
	{
		return 346;
	}

	// Прочитать пакет
	void CCreatePasswordHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		szPassword = Reader.readString();
	}

	// Обработать пакет
	bool CCreatePasswordHandler::handle(CPlayer& Player)
	{
		// Проверяем валидность пароля
		if (!PKO::CUtils::IsValidSecretPassword(szPassword))
		{
			std::stringstream message;
			message << "bad secret password \"" << szPassword << "\"";
			Player.sendDebug(message.str());

			// Посылаем ошибку
			CCreatePasswordPacket password_packet;
			Player.sendPacket(Player.server(), &password_packet);

			return false;
		}

		return true;
	}

	// Сбросить обработчик
	void CCreatePasswordHandler::reset()
	{
		szPassword = "";
	}

	// Действие после отправки пакета
	void CCreatePasswordHandler::after_send(CPlayer& Player) {



	}

}