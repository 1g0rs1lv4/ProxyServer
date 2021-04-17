#pragma once
#include "../Account/Account.h"

namespace PKO
{

	// Тип шифрования
	enum encrypt_t
	{
		enc_cs = 0,
		enc_sc,
	};

	enum decrypt_t
	{
		dec_cs = 0,
		dec_sc,
	};

	// Класс для шифрование пакетов
	class CPacketEncryptor
	{
		public:

			// Конструктор
			CPacketEncryptor();

			// Деструктор
			~CPacketEncryptor();

			// Получить поля
			bool enabled() const;

			// Установить поля
			void init(bool enabled, const CAccount& account);

			// Зашифровать пакет
			void encrypt(char *data, size_t length, encrypt_t type);
			
			// Расшифровать пакет
			void decrypt(char *data, size_t length, decrypt_t type);

		private:
			
			// Запретим копирование
			CPacketEncryptor(const CPacketEncryptor&) = delete;
			CPacketEncryptor& operator=(const CPacketEncryptor&) = delete;

			// Включено ли шифрование
			bool m_enabled;

			// Длина ключа сессии
			unsigned short int m_session_key_length;

			// Ключ сессии
			char m_session_key[16];

			// Ключи шифрования пакетов
			char m_keys[4][4];


	};


}