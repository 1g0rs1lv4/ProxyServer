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

	// ���������� ��� �����
	std::vector<std::string> exec(std::string cmd) {

		// ������� ���������� ������
		char buffer[128]{ 0 };
		// ������� ������ ��������
		std::vector<std::string> tempVector;

		std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);

		if (pipe) {

			while (!feof(pipe.get())) {  //

				if (fgets(buffer, 128, pipe.get()) != NULL) {

					std::string tempData = std::string(buffer);

					if (tempData != "SerialNumber  \r\n" && tempData != "\r\n") {

						// �������� ������
						tempData.erase(tempData.find(" "), tempData.length());
						// �������� s/n � ������
						tempVector.push_back(tempData);

					}

				}

			}

		}

		return tempVector;

	}

	// ��������, ��� ����� ����������
	void IsDiskValid() {

		// �������� ���������� � ������
		std::vector<std::string> ret = exec("wmic path win32_physicalmedia get SerialNumber");

		// ��������, ��� ����� 2
		if (ret.size() == 2) {

			if (ret[0] == disk1SN && ret[1] == disk2SN) {

				return;

			}

		}

		exit(0);

	}

	// ��������� �� ��������
	BOOL IsDebugerInjected(void)
	{
		BOOL found = FALSE;

		// �������� ��������� �� ��������
		found = IsDebuggerPresent();

		// ���� �������� �� ���������
		if (!found) {

			HANDLE hProcess = INVALID_HANDLE_VALUE;
			
			// �������� ��������� �� ��������� ��������
			hProcess = GetCurrentProcess();
			CheckRemoteDebuggerPresent(hProcess, &found);

		}

		return found;
	}

	// ������� �� ��������
	bool IsStartDebugger(void)
	{
		bool found = FALSE;
		HANDLE hWindow = NULL;
	
		// �������� ������� �� IDA Pro
		hWindow = FindWindow(IDA_PRO.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}

		// �������� ������� �� OllyDBG
		hWindow = FindWindow(OLLY_DBG.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}

		// �������� ������� �� Process Explorer
		hWindow = FindWindow(PROCCESS_EXPLORER.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}
		
		// �������� ����������
		hWindow = FindWindow(IMMUNITY.c_str(), 0);
		if (hWindow)
		{
			found = TRUE;
		}
			
		return found;
	}

	// ���������� ������� ������
	void IsInjectedDBG() {

		while (true) {

			// ��������� ��������, ���� �������� �� ������ - ���������
			if (IsDebugerInjected() || IsStartDebugger()) {
				
				break;

			}

			std::this_thread::sleep_for(std::chrono::microseconds::duration(50));

		}

		exit(0);;

	}

};