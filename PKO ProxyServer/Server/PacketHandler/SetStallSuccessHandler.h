#pragma once
#include "../../Main/IPacketHandler.h"


namespace PKO
{
	// Обработчик пакета успешной установки ларька
	// S -> C
	class CSetStallSuccessHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CSetStallSuccessHandler();

			// Деструктор
			~CSetStallSuccessHandler();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Прочитать пакет
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// Обработать пакет
			virtual bool handle(CPlayer& pPlayer);

			// Действие после отправки пакета
			virtual void after_send(CPlayer& Player);

			// Сбросить обработчик
			virtual void reset();

		private:
			
			// Запретим копирование
			CSetStallSuccessHandler(const CSetStallSuccessHandler&) = delete;
			CSetStallSuccessHandler& operator=(const CSetStallSuccessHandler&) = delete;
	};



}