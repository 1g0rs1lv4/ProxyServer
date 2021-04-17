#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// Обработчик пакета выхода на выбор персонажа
	// C -> S
	class CEndPlayHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CEndPlayHandler();

			// Деструктор
			~CEndPlayHandler();

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
			CEndPlayHandler(const CEndPlayHandler&) = delete;
			CEndPlayHandler& operator=(const CEndPlayHandler&) = delete;

	};

}