#pragma once
#include <string>

namespace PKO
{

	// Максимальное количество ячеек
	const unsigned int MAX_CELL_NUM = 18;

	// Структура ячейки
	struct SStallCell
	{
		unsigned int grid;
		unsigned int money;
		unsigned int count;
		unsigned int index;
	};

	// Торговый ларек
	class CSetStall
	{
		public:

			// Конструктор
			CSetStall();

			// Деструктор
			~CSetStall();

			// Инициализировать ларек
			void init();

			// Установить поля
			void setName(const std::string& name);
			void setCell(const SStallCell& Cell);
			void updateCell(unsigned int grid, unsigned int n);
			void setInstalled(bool i);
			void setCellCount(unsigned int n);
			
			// Получить поля
			const std::string& getName() const;
			bool installed() const;
			bool empty() const;
			unsigned int getCellCount() const;
			const SStallCell& getCell(unsigned int i);
			unsigned int getInstallTick() const;
			unsigned int getInstallTime() const;

		private:

			// Установлен ли ларек
			bool m_installed;

			// Время установки (в тиках)
			unsigned int m_set_tick;

			// Время установки в секундах
			unsigned int m_set_time;

			// Название ларька
			std::string m_name;

			// Количество предметов
			unsigned int m_item_counter;

			// Количество ячеек
			unsigned int m_cell_number;

			// Ячейки ларька
			SStallCell m_Cells[MAX_CELL_NUM];



	};

}
