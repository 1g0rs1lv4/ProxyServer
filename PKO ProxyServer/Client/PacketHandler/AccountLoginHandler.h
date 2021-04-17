#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// Обработчик логин пакета
	// C -> S
	class CAccountLoginHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CAccountLoginHandler();

			// Деструктор
			~CAccountLoginHandler();

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
			CAccountLoginHandler(const CAccountLoginHandler&) = delete;
			CAccountLoginHandler& operator=(const CAccountLoginHandler&) = delete;
	
			std::string m_nobill;
			std::string m_login;
			std::string m_password;
			std::string m_mac;
			unsigned short int m_flag;
			unsigned short int m_version;

			// Версия Защиты 1 
			unsigned short int p_version_1;
			// Версия Защиты 2
			unsigned short int p_version_2;
	};

}
