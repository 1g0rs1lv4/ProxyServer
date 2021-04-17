#pragma once
#include <string>

namespace PKO
{

	// ������������ ���������� �����
	const unsigned int MAX_CELL_NUM = 18;

	// ��������� ������
	struct SStallCell
	{
		unsigned int grid;
		unsigned int money;
		unsigned int count;
		unsigned int index;
	};

	// �������� �����
	class CSetStall
	{
		public:

			// �����������
			CSetStall();

			// ����������
			~CSetStall();

			// ���������������� �����
			void init();

			// ���������� ����
			void setName(const std::string& name);
			void setCell(const SStallCell& Cell);
			void updateCell(unsigned int grid, unsigned int n);
			void setInstalled(bool i);
			void setCellCount(unsigned int n);
			
			// �������� ����
			const std::string& getName() const;
			bool installed() const;
			bool empty() const;
			unsigned int getCellCount() const;
			const SStallCell& getCell(unsigned int i);
			unsigned int getInstallTick() const;
			unsigned int getInstallTime() const;

		private:

			// ���������� �� �����
			bool m_installed;

			// ����� ��������� (� �����)
			unsigned int m_set_tick;

			// ����� ��������� � ��������
			unsigned int m_set_time;

			// �������� ������
			std::string m_name;

			// ���������� ���������
			unsigned int m_item_counter;

			// ���������� �����
			unsigned int m_cell_number;

			// ������ ������
			SStallCell m_Cells[MAX_CELL_NUM];



	};

}
