#pragma once
#include <string>

namespace PKO
{

	// Класс игрового аккаунта
	class CAccount
	{
		public:

			// Конструктор
			CAccount();

			// Деструктор
			~CAccount();

			// Установить поля
			void setLogin(const std::string& login);
			void setPassword(const std::string& password);
			void setMacAddress(const std::string& mac_address);
			void setChapString(const std::string& chap_string);
			void setBillString(const std::string& bill_string);
			void setFlag(unsigned short int flag);
			void setVersion(unsigned short int version);
			void setEncryptionKey(const char *key, size_t length);

			// Получить поля
			const std::string& getLogin() const;
			const std::string& getPassword() const;
			const std::string& getMacAddress() const;
			const std::string& getChapString() const;
			const std::string& getBillString() const;
			unsigned short int getFlag() const;
			unsigned short int getVersion() const;
			const char *getEncryptionKey() const;
			size_t getEncryptionKeyLength() const;

		private:
			
			// Логин
			std::string m_login;

			// Пароль
			std::string m_password;

			// MAC
			std::string m_mac_address;

			// Строка со временем подключения
			std::string m_chap_string;

			// Биллинг
			std::string m_bill_string;

			// Флаг
			unsigned int m_flag;

			// Версия клиента
			unsigned int m_version;

			// Длина ключа шифрования пакетов
			size_t m_encryption_key_length;

			// Ключ шифрования пакетов
			char m_encryption_key[12];

	};


}