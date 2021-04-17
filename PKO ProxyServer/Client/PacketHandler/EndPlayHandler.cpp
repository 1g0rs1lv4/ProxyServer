#include "EndPlayHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <iostream>

namespace PKO
{
	// Конструктор
	CEndPlayHandler::CEndPlayHandler()
	{

	}

	// Деструктор
	CEndPlayHandler::~CEndPlayHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CEndPlayHandler::getId() const
	{
		return 434;
	}


	// Прочитать пакет 
	void CEndPlayHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// Обработать пакет
	bool CEndPlayHandler::handle(CPlayer& Player)
	{

		/*PKO::CSetStall playerStall = Player.character().stall();

		// Если установлен ларек
		if (playerStall.installed()) {

			// Обнулим ларек
			playerStall.setInstalled(false);
			playerStall.setCellCount(0);

		}

		*/
		
		return true;

	}

	// Сбросить обработчик
	void CEndPlayHandler::reset()
	{
		
	}

	// Действие после отправки пакета
	void CEndPlayHandler::after_send(CPlayer& Player) {



	}

}