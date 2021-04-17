#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	class CSysInfoHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CSysInfoHandler();

			// Деструктор
			~CSysInfoHandler();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Прочитать пакет
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// Обработать пакет
			virtual bool handle(CPlayer& Player);

			// Сбросить пакет
			virtual void reset();

		private:
			
			// Запрещаем копирование
			CSysInfoHandler(const CSysInfoHandler&) = delete;
			CSysInfoHandler& operator=(const CSysInfoHandler&) = delete;

			// Строка с сообщением
			std::string m_message;

	};

}
