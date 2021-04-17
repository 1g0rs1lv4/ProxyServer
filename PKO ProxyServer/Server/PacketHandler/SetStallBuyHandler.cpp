#include "SetStallBuyHandler.h"
#include "../../Class/Player/Player.h"
#include "../../Binary/BinaryReader.h"
#include "../../Client/Packet/DisconnectPacket.h"

namespace PKO
{
	// Конструктор
	CSetStallBuyHandler::CSetStallBuyHandler() :
		m_cha_id(0), m_grid_id(0), m_item_count(0)
	{

	}

	// Деструктор
	CSetStallBuyHandler::~CSetStallBuyHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CSetStallBuyHandler::getId() const
	{
		return 856;
	}

	// Прочитать пакет
	void CSetStallBuyHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		// Читаем ID персонажа
		m_cha_id = Reader.readUint32();
		
		// Читаем ID ячейки
		m_grid_id = static_cast<unsigned int>(Reader.readByte());
		
		// Читаем количество предметов
		m_item_count = static_cast<unsigned int>(Reader.readByte());
	}

	// Обработать пакет
	bool CSetStallBuyHandler::handle(CPlayer& Player)
	{
		if (Player.character().getId() == m_cha_id)
		{
			if (Player.character().stall().installed())
			{
				// Обновляем количество предметов в ячейке
				Player.character().stall().updateCell(m_grid_id, m_item_count);

				// Отключаем игрока, если ларек пуст
				if (Player.stall_server()->config().auto_close_on_empty())
				{
					if (Player.character().stall().empty() &&
						!Player.server()->connected())
					{
						CDisconnectPacket disconnect_packet(Player, "Empty stall.");
						Player.sendPacket(Player.client(), &disconnect_packet);
						return false;
					}
				}
			}
		}

		return true;
	}

	// Сбросить обработчик
	void CSetStallBuyHandler::reset()
	{
		m_cha_id = 0;
		m_grid_id = 0;
		m_item_count = 0;
	}

	// Действие после отправки пакета
	void CSetStallBuyHandler::after_send(CPlayer& Player) {



	}

}
