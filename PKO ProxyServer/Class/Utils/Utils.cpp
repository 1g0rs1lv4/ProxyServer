#include "Utils.h"
#include <algorithm>
#include <event2\listener.h>
#include <regex>

namespace PKO
{
	// �������� IP ����� �� ��������� ������
	std::string CUtils::GetIpAddress(sockaddr_in *sockaddr)
	{
		char remote_addr[INET_ADDRSTRLEN];
		InetNtopA(AF_INET, &sockaddr->sin_addr, remote_addr, sizeof(remote_addr));

		return std::string(remote_addr);
	}

	// �������� ������ � ������� ��������
	std::string CUtils::LowerCase(const std::string& str)
	{
		std::string lower = str;
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
		
		return lower;
	}

	// ������� �� ������ �������
	std::string CUtils::TrimString(std::string str)
	{
		size_t start_pos, end_pos;

		// ������� ������� � ������ ������
		start_pos = str.find_first_not_of(" \t");
		if (std::string::npos != start_pos) {
			str = str.substr(start_pos);
		}

		// ������� ������� � ����� ������
		end_pos = str.find_last_not_of(" \t");
		if (std::string::npos != end_pos) {
			str = str.substr(0, end_pos + 1);
		}

		return str;
	}

	// ������� �� ������ �����������
	std::string CUtils::DeleteComments(std::string str)
	{
		// ���� ����������� � ������
		size_t comment = str.find("//");
		if (comment != std::string::npos) {
			return str.substr(0, comment);
		}

		return str;
	}

	// �������� ���� �� ������������ �����
	std::string CUtils::ExtractFilePath(const std::string& path)
	{
		size_t found = path.find_last_of("/\\");
		return path.substr(0, found);
	}

	// �������� ��� ������������ �����
	std::string CUtils::ExtractFileName(const std::string& path)
	{
		size_t found = path.find_last_of("/\\");
		return path.substr(found + 1);
	}

	// �������� ���������� �����
	std::string CUtils::ChangeFileExt(const std::string& path, const std::string& ext)
	{
		size_t found = path.find_last_of('.');
		return path.substr(0, found + 1) + ext;
	}

	// �������� ���� �� ������������ �����
	std::string CUtils::GetApplicationPath()
	{
		char path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);

		return std::string(path);
	}

	// �������� ���������� ����
	bool CUtils::IsValidSecretPassword(const std::string str)
	{
		std::regex pattern("^([A-F0-9]){32}$");
		return std::regex_match(str, pattern);
	}

	// �������� ��� �������
	bool CUtils::IsValidMac(const std::string str)
	{
		std::regex pattern("^([A-Z0-9]{2}(-)){6,7}[A-Z0-9]{2}$");
		return std::regex_match(str, pattern);
	}

	// �������� �������� ������
	bool CUtils::IsValidStallName(const std::string str)
	{
		std::regex pattern("^([�-���, !.0-9]){2,}$");
		return std::regex_match(str, pattern);
	}

} 