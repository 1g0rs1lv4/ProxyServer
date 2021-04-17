#include "SetStall.h"
#include <Windows.h>
#include <ctime>

namespace PKO
{
	// Конструктор
	CSetStall::CSetStall()
	{
		init();
	}

	// Деструктор
	CSetStall::~CSetStall()
	{

	}

	// Инициализировать ларек
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

	// Установить поля
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

	// Удалить предметы из слота
	void CSetStall::updateCell(unsigned int grid, unsigned int n)
	{
		if (grid < MAX_CELL_NUM)
		{
			// Вычитаем количество предметов из ячейки
			m_Cells[grid].count -= n;

			// Закрываем ячейку, если в ней закончились предметы
			if (m_Cells[grid].count == 0)
			{
				m_Cells[grid].index = 0;
				m_Cells[grid].money = 0;
			}

			// Обновляем количество предметов
			m_item_counter -= n;
		}
	}

	// Получить поля
	bool CSetStall::installed() const
	{
		return m_installed;
	}

	// Пуст ли ларек
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

	// Установить название ларька
	void CSetStall::setName(const std::string& name)
	{
		m_name = name;
	}

	// Установить количество ячеек
	void CSetStall::setCellCount(unsigned int n)
	{
		m_cell_number = n;
	}

	// Установить ячейку ларька
	void CSetStall::setCell(const SStallCell& Cell)
	{
		if (Cell.grid < MAX_CELL_NUM && Cell.count > 0)
		{
			// Копируем ячейку
			m_Cells[Cell.grid] = Cell;

			// Считаем количество предметов в ларьке
			m_item_counter += Cell.count;
		}
	}

	// Получить количество ячеек
	unsigned int CSetStall::getCellCount() const
	{
		return m_cell_number;
	}

	// Получить ячейку по индексу
	const SStallCell& CSetStall::getCell(unsigned int i)
	{
		if (i < MAX_CELL_NUM)
		{
			return m_Cells[i];
		}

		return m_Cells[MAX_CELL_NUM - 1];
	}

	// Получить название ларька
	const std::string& CSetStall::getName() const
	{
		return m_name;
	}

}