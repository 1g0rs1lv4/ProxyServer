#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ����� �������� ��������� �� ������
	// S -> C
	class CSetStallBuyHandler : public IPacketHandler
	{
		public:

			// �����������
			CSetStallBuyHandler();

			// ����������
			~CSetStallBuyHandler();

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
			CSetStallBuyHandler(const CSetStallBuyHandler&) = delete;
			CSetStallBuyHandler& operator=(const CSetStallBuyHandler&) = delete;
	
			// ID ���������
			unsigned int m_cha_id;

			// ID ������
			unsigned int m_grid_id;

			// ����������
			unsigned int m_item_count;
	};

}

