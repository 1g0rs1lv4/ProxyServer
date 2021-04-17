#pragma once
#include "../../Main/IPacketHandler.h"
#include "../../Class/Character/Character.h"

namespace PKO
{
	// Точка
	struct SPoint
	{
		unsigned int x;
		unsigned int y;
	};

	class CActionHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CActionHandler();

			// Деструктор
			~CActionHandler();

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
			CActionHandler(const CActionHandler&) = delete;
			CActionHandler& operator=(const CActionHandler&) = delete;

			// ID персонажа
			unsigned int m_cha_id;

			// ID действия
			unsigned int m_action_id;

			// Состояние
			unsigned int m_state;

			// Количество точек
			unsigned int m_point_number;

			// Точки
			SPoint m_Points[32];

			// Размер инвентаря
			unsigned int m_kitbag_size;

			// Ячейки инвентаря
			SKitbagGrid m_kitbagCells[MAX_KITBAG_SIZE];


	};

};

