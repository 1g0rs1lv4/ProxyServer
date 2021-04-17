#pragma once
#include <string>
#include "../../Main/IPacket.h"

namespace PKO
{
	// Логин пакет
	// C -> S
	class CLoginPacket : public IPacket
	{
		public:

			// Конструктор
			CLoginPacket();

			// Деструктор
			~CLoginPacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);

			// Установить поля
			void setNobill(const std::string& nobill);
			void setLogin(const std::string& login);
			void setPassword(const std::string& password);
			void setMacAddress(const std::string& mac_address);
			void setIpAddress(const std::string& ip_address);
			void setChapString(const std::string& chap_string);
			void setFlag(unsigned short int flag);
			void setVersion(unsigned short int version);
			
		private:
			
			// Запретим копирование
			CLoginPacket(const CLoginPacket&) = delete;
			CLoginPacket& operator=(const CLoginPacket&) = delete;

			// nobill
			std::string m_nobill;

			// Логин
			std::string m_login;

			// Пароль
			std::string m_password;

			// MAC
			std::string m_mac_address;

			// Флаг 911
			unsigned short int m_flag;

			// Версия игры
			unsigned short int m_version;

			// Строка с веременем подключения
			std::string m_chap_string;

			// IP адрес
			std::string m_ip_address;

	};

}
