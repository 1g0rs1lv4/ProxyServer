#pragma once
#include <Windows.h>
#include <iostream>

std::string IDA_PRO = "Qt5QWindowIcon";
std::string OLLY_DBG = "OLLYDBG";
std::string PROCCESS_EXPLORER = "PROCEXPL";
std::string IMMUNITY = "ID";

std::string disk1SN = "18031AB99A2C";
std::string disk2SN = "WL13ZRWC";

namespace ProcessProtection {

	// Возвращаем все диски
	std::vector<std::string> exec(std::string cmd) {

		// Создаем переменнуб буфера
		char buffer[128]{ 0 };
		// Создаем вектор возврата
		std::vector<std::string> tempVector;

		std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);

		if (pipe) {

			while (!feof(pipe.get())) {  //

				if (fgets(buffer, 128, pipe.get()) != NULL) {

					std::string tempData = std::string(buffer);

					if (tempData != "SerialNumber  \r\n" && tempData != "\r\n") {

						// Обрезает строку
						tempData.erase(tempData.find(" "), tempData.length());
						// Помещаем s/n в вектор
						tempVector.push_back(tempData);

					}

				}

			}

		}

		return tempVector;

	}

	// Убедимся, что диски существуют
	void IsDiskValid() {

		// Получаем информацию о дисках
		std::vector<std::string> ret = exec("wmic path win32_physicalmedia get SerialNumber");

		// Убедимся, что диска 2
		if (ret.size() == 2) {

			if (ret[0] == disk1SN && ret[1] == disk2SN) {

				return;

			}

		}

		exit(0);

	}

	// Подключен ли отладчик
	BOOL IsDebugerInjected(void)
	{
		BOOL found = FALSE;

		// Проверим подключен ли отладчик
		found = IsDebuggerPresent();

		// Если отладчик не подключен
		if (!found) {

			HANDLE hProcess = INVALID_HANDLE_VALUE;
			
			// Проверим подключен ли удаленный отладчик
			hProcess = GetCurrentProcess();
			CheckRemoteDebuggerPresent(hProcess, &found);

		}

		return found;
	}

	// Запущен ли отладчик
	bool IsStartDebugger(void)
	{
		bool found = FALSE;
		HANDLE hWindow = NULL;
	
		// Проверка включен ли IDA Pro
		hWindow = FindWindow(IDA_PRO.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}

		// Проверка включен ли OllyDBG
		hWindow = FindWindow(OLLY_DBG.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}

		// Проверка включен ли Process Explorer
		hWindow = FindWindow(PROCCESS_EXPLORER.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}
		
		// Проверка Иммунитета
		hWindow = FindWindow(IMMUNITY.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}
			
		return found;
	}

	// Обработчик событий защиты
	void IsInjectedDBG() {

		while (true) {

			// Выполняем проверку, если проверку не прошли - выключаем
			if (IsDebugerInjected() || IsStartDebugger()) {
				
				break;

			}

			std::this_thread::sleep_for(std::chrono::microseconds::duration(50));

		}

		exit(0);;

	}

};