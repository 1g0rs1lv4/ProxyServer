#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик смены персональных данных
	// C -> S
	class CCreatePasswordHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CCreatePasswordHandler();

			// Деструктор
			~CCreatePasswordHandler();

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
			CCreatePasswordHandler(const CCreatePasswordHandler&) = delete;
			CCreatePasswordHandler& operator=(const CCreatePasswordHandler&) = delete;

			std::string szPassword;
	};
}