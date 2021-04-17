#pragma once

namespace PKO
{

	// Класс защиты
	class CProtection
	{
		public:

			// Конструктор
			CProtection();

			// Деструктор
			~CProtection();

			// Инициализировать защиту
			void init(bool enabled, unsigned short int ver);

			// Проверить пакет
			bool check_packet(unsigned int n);

			// Проверить пакет
			unsigned short int getVersion() { return m_ver; };

			// Включена ли защита
			bool enabled() const;

		private:

			// Запретим копирование
			CProtection(const CProtection&) = delete;
			CProtection& operator=(const CProtection&) = delete;


			// Включена ли защита
			bool m_enabled;

			// Версия защиты
			unsigned short int m_ver;

			// Счетчик пакетов
			unsigned int m_packet_counter;
	};

}
