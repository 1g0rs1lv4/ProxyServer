#include "SetStallCloseHandler.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// Конструктор
	CSetStallCloseHandler::CSetStallCloseHandler()
	{

	}

	// Деструктор
	CSetStallCloseHandler::~CSetStallCloseHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CSetStallCloseHandler::getId() const
	{
		return 333;
	}

	// Прочитать пакет
	void CSetStallCloseHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// Обработать пакет
	bool CSetStallCloseHandler::handle(CPlayer& Player)
	{
		// Сбросим ларек
		Player.character().stall().init();

		return true;
	}

	// Сбросить обработчик
	void CSetStallCloseHandler::reset()
	{

	}

	// Действие после отправки пакета
	void CSetStallCloseHandler::after_send(CPlayer& Player) {



	}

}