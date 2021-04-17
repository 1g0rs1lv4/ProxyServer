#include "BeginSeeHandler.h"
#include "../../Class/Player/Player.h"


#define MonsterDiapazon 0xb0000000

namespace PKO
{
	// Конструктор
	CBeginSeeHandler::CBeginSeeHandler()
		: cha_id(0), model_id(0), findPlayer(NULL)
	{

	}

	// Деструктор
	CBeginSeeHandler::~CBeginSeeHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CBeginSeeHandler::getId() const
	{
		return 504;
	}

	// Прочитать пакет
	void CBeginSeeHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{

		// Пропускаем байт
		Reader.seek(1, PKO::seek_cur);

		// Запишем id модели
		model_id = (int) Reader.readUint32();
		// Запишем id персонажа
		cha_id = (int)Reader.readUint32();

		// Убедимся, что персонаж не монстр
		if (cha_id < MonsterDiapazon) {

			// Ищем игрока
			findPlayer = Player.stall_server()->FindPlayerByID(cha_id);

		}
		
	}

	// Обработать пакет
	bool CBeginSeeHandler::handle(CPlayer& Player)
	{

		return true;

	}

	// Сбросить обработчик
	void CBeginSeeHandler::reset()
	{
		cha_id = 0;
		model_id = 0;
		findPlayer = NULL;
	}

	// Действие после отправки пакета
	void CBeginSeeHandler::after_send(CPlayer& Player) {

		// Игрок найден
		if (findPlayer) {

			// Установлен ли ларек
			if (findPlayer->character().stall().installed()) {

				// Онлайн ларек
				if (!findPlayer->server()->connected()) {

					// Создаем пакет и инициализируем его
					//CStallColorPacket stallColor(cha_id, 0xFFFF0000);
					// Отправляем пакет
					//Player.sendPacket(Player.server(), &stallColor);

				} else {

					// Создаем пакет и инициализируем его
					//CStallColorPacket stallColor(cha_id, 0xFF008000);
					// Отправляем пакет
					//Player.sendPacket(Player.server(), &stallColor);

				}

			}

		}

	}

}