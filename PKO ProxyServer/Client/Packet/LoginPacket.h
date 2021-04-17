#pragma once
#include <string>
#include "../../Main/IPacket.h"

namespace PKO
{
	// ����� �����
	// C -> S
	class CLoginPacket : public IPacket
	{
		public:

			// �����������
			CLoginPacket();

			// ����������
			~CLoginPacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);

			// ���������� ����
			void setNobill(const std::string& nobill);
			void setLogin(const std::string& login);
			void setPassword(const std::string& password);
			void setMacAddress(const std::string& mac_address);
			void setIpAddress(const std::string& ip_address);
			void setChapString(const std::string& chap_string);
			void setFlag(unsigned short int flag);
			void setVersion(unsigned short int version);
			
		private:
			
			// �������� �����������
			CLoginPacket(const CLoginPacket&) = delete;
			CLoginPacket& operator=(const CLoginPacket&) = delete;

			// nobill
			std::string m_nobill;

			// �����
			std::string m_login;

			// ������
			std::string m_password;

			// MAC
			std::string m_mac_address;

			// ���� 911
			unsigned short int m_flag;

			// ������ ����
			unsigned short int m_version;

			// ������ � ��������� �����������
			std::string m_chap_string;

			// IP �����
			std::string m_ip_address;

	};

}
