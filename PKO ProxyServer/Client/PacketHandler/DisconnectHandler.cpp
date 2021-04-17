#include "DisconnectHandler.h"
#include "../../Class/Player/Player.h"
#include <sstream>

namespace PKO
{
	// Конструктор
	CDisconnectHandler::CDisconnectHandler()
	{

	}

	// Деструктор
	CDisconnectHandler::~CDisconnectHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CDisconnectHandler::getId() const
	{
		return 432;
	}

	// Прочитать пакет
	void CDisconnectHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// Обработать пакет
	bool CDisconnectHandler::handle(CPlayer& Player)
	{
		if (Player.character().stall().installed() && 
			          !Player.character().stall().empty()) {

			return false;

		}

		Player.on_server_logout();

		return true;
	}

	// Сбросить обработчик
	void CDisconnectHandler::reset()
	{

	}

	// Действие после отправки пакета
	void CDisconnectHandler::after_send(CPlayer& Player) {



	}

}