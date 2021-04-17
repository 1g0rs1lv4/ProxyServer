#pragma once
#include <string>
#include <vector>
#include "../../Class/SetStall/SetStall.h"

namespace PKO
{
	// Максимальный размер инвентаря
	const unsigned int MAX_KITBAG_SIZE = 48;

	// Структура ячейки инвентаря
	struct SKitbagGrid
	{
		short int grid;
		unsigned int item_id;
	};

	// Класс игрового персонажа
	class CCharacter
	{
		public:

			// Конструктор
			CCharacter();

			// Деструктор
			~CCharacter();

			// Установить поля
			void setId(unsigned int cha_id);
			void setName(const std::string& cha_name);
			void setMap(const std::string& map_name);
			void setPos(unsigned int x, unsigned int y);
			void setKitbagSize(unsigned int size);
			void setGm(const char lv);

			// Получить поля
			unsigned int getId() const;
			const std::string& getName() const;
			const std::string& getMap() const;
			unsigned int getPosX() const;
			unsigned int getPosY() const;
			unsigned int getKitbagSize() const;
			CSetStall& stall();
			std::vector<SKitbagGrid>& kitbag();
			bool IsPKSilver() const;


		private:

			// ID персонажа
			unsigned int m_cha_id;

			// Гм Уровень
			char m_gm;

			// Имя персонажа
			std::string m_cha_name;

			// Карта 
			std::string m_map_name;

			// Координаты X и Y
			unsigned short int m_pos_x;
			unsigned short int m_pos_y;

			// Ларек
			CSetStall m_stall;
			
			// Размер инвентаря
			unsigned int m_kitbag_size;

			// Инвентарь
			std::vector<SKitbagGrid> m_kitbag;
	};


}