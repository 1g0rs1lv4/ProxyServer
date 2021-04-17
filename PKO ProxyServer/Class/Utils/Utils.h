#pragma once
#include <string>
#include <WinSock2.h>

namespace PKO
{
	// ����� ��� ��������������� �������
	class CUtils
	{
		public:

			// �������� IP ����� �� ��������� ������
			static std::string GetIpAddress(sockaddr_in *sockaddr);

			// �������� ������ � ������� ��������
			static std::string LowerCase(const std::string& str);
			
			// ������� �� ������ �������
			static std::string TrimString(std::string str);

			// ������� �� ������ �����������
			static std::string DeleteComments(std::string str);

			// �������� ���� �� ������������ �����
			static std::string ExtractFilePath(const std::string& path);

			// �������� ��� ������������ �����
			static std::string ExtractFileName(const std::string& path);

			// �������� ���������� �����
			static std::string ChangeFileExt(const std::string& path, const std::string& ext);

			// �������� ���� �� ������������ �����
			static std::string GetApplicationPath();

			// �������� ���������� ����
			static bool IsValidSecretPassword(const std::string str);

			// �������� ��� �������
			static bool IsValidMac(const std::string str);

			// �������� �������� ������
			static bool IsValidStallName(const std::string str);
	
	};
}

