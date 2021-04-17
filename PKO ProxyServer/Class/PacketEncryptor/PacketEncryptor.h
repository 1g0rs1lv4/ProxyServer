#pragma once
#include "../Account/Account.h"

namespace PKO
{

	// ��� ����������
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

	// ����� ��� ���������� �������
	class CPacketEncryptor
	{
		public:

			// �����������
			CPacketEncryptor();

			// ����������
			~CPacketEncryptor();

			// �������� ����
			bool enabled() const;

			// ���������� ����
			void init(bool enabled, const CAccount& account);

			// ����������� �����
			void encrypt(char *data, size_t length, encrypt_t type);
			
			// ������������ �����
			void decrypt(char *data, size_t length, decrypt_t type);

		private:
			
			// �������� �����������
			CPacketEncryptor(const CPacketEncryptor&) = delete;
			CPacketEncryptor& operator=(const CPacketEncryptor&) = delete;

			// �������� �� ����������
			bool m_enabled;

			// ����� ����� ������
			unsigned short int m_session_key_length;

			// ���� ������
			char m_session_key[16];

			// ����� ���������� �������
			char m_keys[4][4];


	};


}