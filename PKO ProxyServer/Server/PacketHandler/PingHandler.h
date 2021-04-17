#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик запроса на пинг
	// S -> C
	class CPingHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CPingHandler();

			// Деструктор
			~CPingHandler();

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
			CPingHandler(const CPingHandler&) = delete;
			CPingHandler& operator=(const CPingHandler&) = delete;


	};

}
