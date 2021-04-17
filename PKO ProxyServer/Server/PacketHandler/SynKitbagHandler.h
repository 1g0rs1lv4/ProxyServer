#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	class CSynKitbagHandler : public IPacketHandler
	{
		public:

			//	Конструктор
			CSynKitbagHandler();

			// Деструктор
			~CSynKitbagHandler();

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
			CSynKitbagHandler(const CSynKitbagHandler&) = delete;
			CSynKitbagHandler& operator=(const CSynKitbagHandler&) = delete;

			// ID персонажа
			unsigned int m_cha_id;

			// Новый размер инвентаря
			unsigned int m_new_size;
	};
};

