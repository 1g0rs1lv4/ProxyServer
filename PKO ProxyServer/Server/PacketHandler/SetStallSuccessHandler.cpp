#include "SetStallSuccessHandler.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// Конструктор
	CSetStallSuccessHandler::CSetStallSuccessHandler()
	{

	}

	// Деструктор
	CSetStallSuccessHandler::~CSetStallSuccessHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CSetStallSuccessHandler::getId() const
	{
		return 858;
	}

	// Прочитать пакет
	void CSetStallSuccessHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

	}

	// Обработать пакет
	bool CSetStallSuccessHandler::handle(CPlayer& Player)
	{

		// Посчитаем кол-во игроков с таким же IP
		unsigned int max_ip = Player.stall_server()->config().max_stalls_per_ip();
		if (max_ip > 0)
		{
			unsigned int n = 0;
			const player_list_t& players = Player.stall_server()->getPlayers();
			auto i = players.begin();
			while (i != players.end())
			{
				if ( (*i)->character().stall().installed() == true )
				{
					if ( (*i)->server()->getIpAddress() ==
							Player.server()->getIpAddress() )
					{
						n++;
						if (n >= max_ip)
						{
							Player.character().stall().setInstalled(false);
							return true;
						}
					}
				}

				i++;
			}
		}

		// Получим список разрешенных карт
		const map_list_t& maps = Player.stall_server()->config().map_list();

		// Проверим, что игрок находится на разрешенной карте
		auto it = std::find(maps.begin(), maps.end(), Player.character().getMap());

		if (it != maps.end()) {

			Player.character().stall().setInstalled(true);

		} else {

			Player.character().stall().setInstalled(false);

		}

		return true;
	}

	// Сбросить обработчик
	void CSetStallSuccessHandler::reset()
	{

	}

	// Действие после отправки пакета
	void CSetStallSuccessHandler::after_send(CPlayer& Player) {



	}

}