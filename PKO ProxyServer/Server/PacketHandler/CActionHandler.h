#pragma once
#include "../../Main/IPacketHandler.h"
#include "../../Class/Character/Character.h"

namespace PKO
{
	// �����
	struct SPoint
	{
		unsigned int x;
		unsigned int y;
	};

	class CActionHandler : public IPacketHandler
	{
		public:

			// �����������
			CActionHandler();

			// ����������
			~CActionHandler();

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
			CActionHandler(const CActionHandler&) = delete;
			CActionHandler& operator=(const CActionHandler&) = delete;

			// ID ���������
			unsigned int m_cha_id;

			// ID ��������
			unsigned int m_action_id;

			// ���������
			unsigned int m_state;

			// ���������� �����
			unsigned int m_point_number;

			// �����
			SPoint m_Points[32];

			// ������ ���������
			unsigned int m_kitbag_size;

			// ������ ���������
			SKitbagGrid m_kitbagCells[MAX_KITBAG_SIZE];


	};

};

