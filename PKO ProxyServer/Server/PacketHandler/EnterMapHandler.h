#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"
#include "../../Class/Character/Character.h"

namespace PKO
{
	// ���������� ������ ����� �� �����
	// S -> C
	class CEnterMapHandler : public IPacketHandler
	{
		public:
			
			// �����������
			CEnterMapHandler();

			// ����������
			~CEnterMapHandler();

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
			CEnterMapHandler(const CEnterMapHandler&) = delete;
			CEnterMapHandler& operator=(const CEnterMapHandler&) = delete;

			// ID ���������
			unsigned int m_cha_id;

			// ��� ���������
			std::string m_cha_name;
			
			// �� �������
			char m_gm;

			// �������� �����
			std::string m_map_name;

			// ���������� X, Y
			unsigned int m_pos_x;
			unsigned int m_pos_y;

			// ������ ���������
			unsigned int m_kitbag_size;

			// ������ ��������
			SKitbagGrid m_kitbagGrids[MAX_KITBAG_SIZE];

	};
}



