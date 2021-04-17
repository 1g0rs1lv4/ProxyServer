#include "PingHandler.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/PingPacket.h"

namespace PKO
{
	// Конструктор
	CPingHandler::CPingHandler()
	{

	}

	// Деструктор
	CPingHandler::~CPingHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CPingHandler::getId() const
	{
		return 537;
	}

	// Прочитать пакет
	void CPingHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// Обработать пакет
	bool CPingHandler::handle(CPlayer& Player)
	{
		// Отправляем серверу пинг пакета
		if (!Player.server()->connected())
		{
			CPingPacket ping_packet;
			Player.sendPacket(Player.client(), &ping_packet);

			return false;
		}

		return true;
	}

	// Сбросить обработчик
	void CPingHandler::reset()
	{

	}

	// Действие после отправки пакета
	void CPingHandler::after_send(CPlayer& Player) {



	}

}