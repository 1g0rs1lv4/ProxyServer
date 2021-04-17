#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Пакет удаления предметов из ларька
	// S -> C
	class CSetStallBuyHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CSetStallBuyHandler();

			// Деструктор
			~CSetStallBuyHandler();

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
				
			// Запретим копирование
			CSetStallBuyHandler(const CSetStallBuyHandler&) = delete;
			CSetStallBuyHandler& operator=(const CSetStallBuyHandler&) = delete;
	
			// ID персонажа
			unsigned int m_cha_id;

			// ID ячейки
			unsigned int m_grid_id;

			// Количество
			unsigned int m_item_count;
	};

}

