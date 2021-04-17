#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"
#include "../../Class/SetStall/SetStall.h"

namespace PKO
{
	// Обработчик пакета с информацией о ларьке
	// C -> S
	class CSetStallInfoHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CSetStallInfoHandler();

			// Деструктор
			~CSetStallInfoHandler();

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
			CSetStallInfoHandler(const CSetStallInfoHandler&) = delete;
			CSetStallInfoHandler& operator=(const CSetStallInfoHandler&) = delete;

			// Название ларька
			std::string m_name;

			// Количество слотов
			unsigned int m_slot_number;

			// Ячейки
			SStallCell m_cells[18];
	};

}
