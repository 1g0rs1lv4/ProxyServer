#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>

// Включаем классы
#include "../Class/Settings/Settings.h"
#include "../Class/ProxyServer/ProxyServer.h"
#include "../Class/Utils/Utils.h"


// Обработчик консоли
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

// Напечатать цветом
void WriteColorText(HANDLE handle, std::string str, WORD color) {

	SetConsoleTextAttribute(handle, color);
	std::cout << str;
	SetConsoleTextAttribute(handle, 7);

}

// Напечатать приветственное сообщение
void Settings(PKO::CSettings & settings, std::string cfg_path);

// Напечатать инфо о настройках
void Welcome();

// Загрузить библиотеку WinSock 2.2
void InitWinsock2();

// Выгрузить библиотку WinSock 2.2
void FreeWinsock2();

// Точка входа
int main(int argc, char *argv[])
{

	// Напечатаем привественное сообщение
	Welcome();

	// Загружаем библиотеку WinSock 2.2
	InitWinsock2();

	// Создаем сервер
	try 
	{

		// Создаем объект настроек сервера
		PKO::CSettings Config;

		// Создаем сервер ларьков
		PKO::CProxyServer Server(Config);

		// Путь до настроек
		std::string cfg_path = PKO::CUtils::ChangeFileExt(PKO::CUtils::GetApplicationPath(), "cfg");
		
		// Загружаем настройки
		Config.load(cfg_path);

		std::stringstream input;

		for (int i = 1; i < argc; ++i)
		{
			input << argv[i] << std::endl;
		}

		std::string param;
		while (std::getline(input, param, ' '))
		{
			param = PKO::CUtils::TrimString(param);
			size_t p = param.find(':');
			if (p != std::string::npos)
			{
				std::string name = PKO::CUtils::TrimString(param.substr(0, p));
				if (!name.length()) continue;
				std::string value = PKO::CUtils::TrimString(param.substr(p + 1, param.length() - (p + 1)));
				if (!value.length()) continue;
				if (name == "port")
				{
					try {
						unsigned short int port = static_cast<unsigned short int>(std::stoi(value));
						if (port > 0 && port != 80 && port < 65536)
						{
							Config.setListenPort(port);
						}
					}
					catch (...) {

					}
				}
			}
		}


		// Напечатаем включенные настройки
		Settings(Config, cfg_path);

		// Запускаем сервер ларьков
		Server.run();

	}
	catch (const PKO::settings_exception &e) {
		std::cout << e.what() << std::endl;
	}
	catch (const PKO::stall_server_exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error! Contact the author of this program." << std::endl;
	}

	// Выгружаем библиотеку Winsock2
	FreeWinsock2();

	system("PAUSE");
    return 0;
}

// Напечатать приветственное сообщение
void Welcome()
{
	
	// Автор исходного кода White
	std::cout << "Proxy Server Release!" << std::endl;
	std::cout << "Version ";
	WriteColorText(handle, "1.3.1", 14);
	std::cout << " (";
	WriteColorText(handle, "12/04/2021", 11);
	std::cout << ")" << std::endl << std::endl;
	
	char buffer[32];
	auto current_time = std::chrono::system_clock::now();
	std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
	ctime_s(buffer, sizeof(buffer), &current_time_t);
	std::cout << "Start Date: ";
	WriteColorText(handle, buffer, 12);

}

// Напечатать включенные настройки
void Settings(PKO::CSettings& settings, std::string cfg_path) {


	// Выводим сообщение пользоваелю, что настройки были загружены
	std::cout << "Settings Path: ";
	WriteColorText(handle, cfg_path, 14);
	std::cout << std::endl << std::endl;

	std::cout << "[Settings Parameter]" << std::endl << std::endl;

	int maxConnect = settings.max_connect();
	if (maxConnect) {

		std::cout << " - Max connect: ";
		WriteColorText(handle, std::to_string(maxConnect), 15);
		std::cout << std::endl;

	}

	int interval = settings.connect_interval();
	if (interval) {

		std::cout << " - Connect interval: ";
		WriteColorText(handle, std::to_string(interval) + "ms", 15);
		std::cout << std::endl;

	}

	std::cout << std::endl;

}

// Загрузить библиотеку WinSock 2.2
void InitWinsock2()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSAData wsaData;

	if (FAILED(WSAStartup(wVersionRequested, &wsaData))) {
		std::cout << "Couldn't load WinSock 2.2 library!" << std::endl;
		std::cout << "Error code: " << EVUTIL_SOCKET_ERROR() << std::endl;
		return;
	}

	// Отключим курсор
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = false;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(handle, &CCI);

}

// Выгрузить библиотку WinSock 2.2
void FreeWinsock2()
{
	WSACleanup();
}