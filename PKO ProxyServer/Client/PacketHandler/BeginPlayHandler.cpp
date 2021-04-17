#include "BeginPlayHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <iostream>

namespace PKO
{
	// Конструктор
	CBeginPlayHandler::CBeginPlayHandler()
	{

	}

	// Деструктор
	CBeginPlayHandler::~CBeginPlayHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CBeginPlayHandler::getId() const
	{

		return 433;

	}


	// Прочитать пакет 
	void CBeginPlayHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

		// Считаем выбранного персонажа
		selectCha = Reader.readString();

	}

	// Обработать пакет
	bool CBeginPlayHandler::handle(CPlayer& Player)
	{

		return true;

	}

	// Сбросить обработчик
	void CBeginPlayHandler::reset()
	{

	}

	// Действие после отправки пакета
	void CBeginPlayHandler::after_send(CPlayer& Player) {



	}
}