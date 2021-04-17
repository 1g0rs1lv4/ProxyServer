#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик пакета со строкой с датой и временем подключения
	// S -> C
	class CChapStringHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CChapStringHandler();

			// Деструктор
			~CChapStringHandler();

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
			CChapStringHandler(const CChapStringHandler&) = delete;
			CChapStringHandler& operator=(const CChapStringHandler&) = delete;

			// Строка со временем подключения
			std::string m_chap_string;
	};

}
