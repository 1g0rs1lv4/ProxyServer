#pragma once
#include <string>
#include <WinSock2.h>

namespace PKO
{
	// Класс для вспомогательных функций
	class CUtils
	{
		public:

			// Получить IP адрес из структуры адреса
			static std::string GetIpAddress(sockaddr_in *sockaddr);

			// Привести строку к нижнему регистру
			static std::string LowerCase(const std::string& str);
			
			// Удалить из строки пробелы
			static std::string TrimString(std::string str);

			// Удалить из строки комментарии
			static std::string DeleteComments(std::string str);

			// Получить путь до исполняемого файла
			static std::string ExtractFilePath(const std::string& path);

			// Получить имя исполняемого файла
			static std::string ExtractFileName(const std::string& path);

			// Изменить расширение файла
			static std::string ChangeFileExt(const std::string& path, const std::string& ext);

			// Получить путь до исполняемого файла
			static std::string GetApplicationPath();

			// Проверка Секретного кода
			static bool IsValidSecretPassword(const std::string str);

			// Проверка Мак адресса
			static bool IsValidMac(const std::string str);

			// Проверка Названия Ларька
			static bool IsValidStallName(const std::string str);
	
	};
}

