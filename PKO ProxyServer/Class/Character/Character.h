#pragma once
#include <string>
#include <vector>
#include "../../Class/SetStall/SetStall.h"

namespace PKO
{
	// ������������ ������ ���������
	const unsigned int MAX_KITBAG_SIZE = 48;

	// ��������� ������ ���������
	struct SKitbagGrid
	{
		short int grid;
		unsigned int item_id;
	};

	// ����� �������� ���������
	class CCharacter
	{
		public:

			// �����������
			CCharacter();

			// ����������
			~CCharacter();

			// ���������� ����
			void setId(unsigned int cha_id);
			void setName(const std::string& cha_name);
			void setMap(const std::string& map_name);
			void setPos(unsigned int x, unsigned int y);
			void setKitbagSize(unsigned int size);
			void setGm(const char lv);

			// �������� ����
			unsigned int getId() const;
			const std::string& getName() const;
			const std::string& getMap() const;
			unsigned int getPosX() const;
			unsigned int getPosY() const;
			unsigned int getKitbagSize() const;
			CSetStall& stall();
			std::vector<SKitbagGrid>& kitbag();
			bool IsPKSilver() const;


		private:

			// ID ���������
			unsigned int m_cha_id;

			// �� �������
			char m_gm;

			// ��� ���������
			std::string m_cha_name;

			// ����� 
			std::string m_map_name;

			// ���������� X � Y
			unsigned short int m_pos_x;
			unsigned short int m_pos_y;

			// �����
			CSetStall m_stall;
			
			// ������ ���������
			unsigned int m_kitbag_size;

			// ���������
			std::vector<SKitbagGrid> m_kitbag;
	};


}