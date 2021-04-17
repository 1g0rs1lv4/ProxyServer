#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"
#include "../../Class/Character/Character.h"

namespace PKO
{
	// Обработчик пакета входа на карту
	// S -> C
	class CEnterMapHandler : public IPacketHandler
	{
		public:
			
			// Конструктор
			CEnterMapHandler();

			// Деструктор
			~CEnterMapHandler();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Прочитать пакет
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// Обработать пакет
			virtual bool handle(CPlayer& Player);

			// Действие после отправки пакета
			virtual void after_send(CPlayer& Player);

			// Сбросить обработчик
			virtual void reset();

		private:

			// Запрещаем копирование
			CEnterMapHandler(const CEnterMapHandler&) = delete;
			CEnterMapHandler& operator=(const CEnterMapHandler&) = delete;

			// ID персонажа
			unsigned int m_cha_id;

			// Имя персонажа
			std::string m_cha_name;
			
			// Гм уровень
			char m_gm;

			// Название карты
			std::string m_map_name;

			// Координаты X, Y
			unsigned int m_pos_x;
			unsigned int m_pos_y;

			// Размер инвентаря
			unsigned int m_kitbag_size;

			// Ячейки инвенаря
			SKitbagGrid m_kitbagGrids[MAX_KITBAG_SIZE];

	};
}



