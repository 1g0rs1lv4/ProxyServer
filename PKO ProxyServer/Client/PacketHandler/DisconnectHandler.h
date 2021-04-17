#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// Обработчик пакета отключения от сервера
	// C -> S
	class CDisconnectHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CDisconnectHandler();

			// Деструктор
			~CDisconnectHandler();

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
			CDisconnectHandler(const CDisconnectHandler&) = delete;
			CDisconnectHandler& operator=(const CDisconnectHandler&) = delete;
	};


}