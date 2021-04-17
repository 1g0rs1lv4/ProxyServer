#include "SetStall.h"
#include <Windows.h>
#include <ctime>

namespace PKO
{
	// �����������
	CSetStall::CSetStall()
	{
		init();
	}

	// ����������
	CSetStall::~CSetStall()
	{

	}

	// ���������������� �����
	void CSetStall::init()
	{
		m_item_counter = 0;
		m_cell_number = 0;
		m_set_tick = 0;
		m_set_time = 0;
		m_name = "";
		m_installed = false;

		for (unsigned int i = 0; i < MAX_CELL_NUM; i++)
		{
			m_Cells[i].grid = i;
			m_Cells[i].count = 0;
			m_Cells[i].money = 0;
		}
	}

	// ���������� ����
	void CSetStall::setInstalled(bool i)
	{
		if (i == true) {
			m_set_tick = GetTickCount();
			m_set_time = static_cast<unsigned int>(std::time(nullptr));
		} 
		else {
			m_set_tick = 0;
		}

		m_installed = i;
	}

	// ������� �������� �� �����
	void CSetStall::updateCell(unsigned int grid, unsigned int n)
	{
		if (grid < MAX_CELL_NUM)
		{
			// �������� ���������� ��������� �� ������
			m_Cells[grid].count -= n;

			// ��������� ������, ���� � ��� ����������� ��������
			if (m_Cells[grid].count == 0)
			{
				m_Cells[grid].index = 0;
				m_Cells[grid].money = 0;
			}

			// ��������� ���������� ���������
			m_item_counter -= n;
		}
	}

	// �������� ����
	bool CSetStall::installed() const
	{
		return m_installed;
	}

	// ���� �� �����
	bool CSetStall::empty() const
	{
		return (m_item_counter == 0);
	}

	unsigned int CSetStall::getInstallTick() const
	{
		return m_set_tick;
	}

	unsigned int CSetStall::getInstallTime() const
	{
		return m_set_time;
	}

	// ���������� �������� ������
	void CSetStall::setName(const std::string& name)
	{
		m_name = name;
	}

	// ���������� ���������� �����
	void CSetStall::setCellCount(unsigned int n)
	{
		m_cell_number = n;
	}

	// ���������� ������ ������
	void CSetStall::setCell(const SStallCell& Cell)
	{
		if (Cell.grid < MAX_CELL_NUM && Cell.count > 0)
		{
			// �������� ������
			m_Cells[Cell.grid] = Cell;

			// ������� ���������� ��������� � ������
			m_item_counter += Cell.count;
		}
	}

	// �������� ���������� �����
	unsigned int CSetStall::getCellCount() const
	{
		return m_cell_number;
	}

	// �������� ������ �� �������
	const SStallCell& CSetStall::getCell(unsigned int i)
	{
		if (i < MAX_CELL_NUM)
		{
			return m_Cells[i];
		}

		return m_Cells[MAX_CELL_NUM - 1];
	}

	// �������� �������� ������
	const std::string& CSetStall::getName() const
	{
		return m_name;
	}

}