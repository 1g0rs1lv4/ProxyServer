#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик пакета с запросом закрытия ларька
	// C -> S
	class CSetStallCloseHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CSetStallCloseHandler();

			// Деструктор
			~CSetStallCloseHandler();

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
			CSetStallCloseHandler(const CSetStallCloseHandler&) = delete;
			CSetStallCloseHandler& operator=(const CSetStallCloseHandler&) = delete;

	};
}

