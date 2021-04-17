#pragma once
#include "../../Main/IPacketHandler.h"


namespace PKO
{
	// ���������� ������ �������� ��������� ������
	// S -> C
	class CSetStallSuccessHandler : public IPacketHandler
	{
		public:

			// �����������
			CSetStallSuccessHandler();

			// ����������
			~CSetStallSuccessHandler();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// ��������� �����
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// ���������� �����
			virtual bool handle(CPlayer& pPlayer);

			// �������� ����� �������� ������
			virtual void after_send(CPlayer& Player);

			// �������� ����������
			virtual void reset();

		private:
			
			// �������� �����������
			CSetStallSuccessHandler(const CSetStallSuccessHandler&) = delete;
			CSetStallSuccessHandler& operator=(const CSetStallSuccessHandler&) = delete;
	};



}