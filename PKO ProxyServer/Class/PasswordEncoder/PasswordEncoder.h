#pragma once
#include <string>

namespace PKO
{

	// Класс для шифрования паролей
	class CPasswordEncoder
	{
		public:

			// Конструктор
			CPasswordEncoder();

			// Деструктор
			~CPasswordEncoder();

			// Установить пароль и время подключения
			void set_password(const std::string& password);
			void set_chap_string(const std::string& chap_string);

			// Получить пароль и время подключения
			const std::string& get_password() const;
			const std::string& get_chap_stirng() const;

			// Зашифровать пароль
			void encode(char *encoded_password, unsigned short int &length);



		private:

			// Строка со временем подключения
			std::string m_chap_string;

			// Пароль
			std::string m_password;
	};


}