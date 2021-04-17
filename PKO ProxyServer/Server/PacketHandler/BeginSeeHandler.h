#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик отрисовки персонажей
	// S -> C
	class CBeginSeeHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CBeginSeeHandler();

			// Деструктор
			~CBeginSeeHandler();

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
			CBeginSeeHandler(const CBeginSeeHandler&) = delete;
			CBeginSeeHandler& operator=(const CBeginSeeHandler&) = delete;

			// Ид персонажа
			int cha_id;
			// Ид модели
			int model_id;

			// Нужный персонаж
			CPlayer* findPlayer;

	};

}
