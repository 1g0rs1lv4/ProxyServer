#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// ���������� ����� ������
	// C -> S
	class CAccountLoginHandler : public IPacketHandler
	{
		public:

			// �����������
			CAccountLoginHandler();

			// ����������
			~CAccountLoginHandler();

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

			// ��������� �����������
			CAccountLoginHandler(const CAccountLoginHandler&) = delete;
			CAccountLoginHandler& operator=(const CAccountLoginHandler&) = delete;
	
			std::string m_nobill;
			std::string m_login;
			std::string m_password;
			std::string m_mac;
			unsigned short int m_flag;
			unsigned short int m_version;

			// ������ ������ 1 
			unsigned short int p_version_1;
			// ������ ������ 2
			unsigned short int p_version_2;
	};

}
