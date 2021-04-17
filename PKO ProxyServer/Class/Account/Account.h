#pragma once
#include <string>

namespace PKO
{

	// ����� �������� ��������
	class CAccount
	{
		public:

			// �����������
			CAccount();

			// ����������
			~CAccount();

			// ���������� ����
			void setLogin(const std::string& login);
			void setPassword(const std::string& password);
			void setMacAddress(const std::string& mac_address);
			void setChapString(const std::string& chap_string);
			void setBillString(const std::string& bill_string);
			void setFlag(unsigned short int flag);
			void setVersion(unsigned short int version);
			void setEncryptionKey(const char *key, size_t length);

			// �������� ����
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
			
			// �����
			std::string m_login;

			// ������
			std::string m_password;

			// MAC
			std::string m_mac_address;

			// ������ �� �������� �����������
			std::string m_chap_string;

			// �������
			std::string m_bill_string;

			// ����
			unsigned int m_flag;

			// ������ �������
			unsigned int m_version;

			// ����� ����� ���������� �������
			size_t m_encryption_key_length;

			// ���� ���������� �������
			char m_encryption_key[12];

	};


}