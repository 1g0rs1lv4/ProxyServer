#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// ���� ������
	enum result_t
	{
		result_success = 0,
		result_wrong_version = 7,
		result_wrong_username = 1001,
		result_wrong_password = 1002,
		result_already_online = 1104,
	};


	// ���������� ������ � ����������� ����� �� ������
	// S -> C
	class CLoginResultHandler : public IPacketHandler
	{
		public:

			// �����������
			CLoginResultHandler();

			// ����������
			~CLoginResultHandler();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// ��������� �����
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// ���������� �����
			virtual bool handle(CPlayer& Player);

			// �������� ����� �������� ������
			virtual void after_send(CPlayer& Player);

			// �������� ����������
			virtual void reset();

		private:

			// �������� �����������
			CLoginResultHandler(const CLoginResultHandler&) = delete;
			CLoginResultHandler& operator=(const CLoginResultHandler&) = delete;

			// ��� ����������
			unsigned short int m_result;

			// ��������� �� ���������� �������
			bool m_comm_encryption;

			// ���� ����������
			char m_encryption_key[12];

			// ����� ����� ����������
			size_t m_encryption_key_length;


	};
}

