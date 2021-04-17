#pragma once

namespace PKO
{
	// Сетевой буфер
	class CNetBuffer
	{
		public:

			// Конструктор
			CNetBuffer(size_t size);

			// Деструктор
			~CNetBuffer();

			// Добавить данные в буфер
			void add(const char *data, size_t length);

			// Удалить данные из буфера
			void remove(size_t length);

			// Очистить буфер
			void clear();

			// Получить указатель на данные
			const char *data() const;

			// Получить размер буфера
			size_t size() const;

			// Получить длину буфера
			size_t length() const;

			// Установить длину буфера
			void set_length(size_t length);

		private:

			// Размер буфера
			size_t m_size;

			// Длина буфера
			size_t m_length;

			// Буфер
			char *m_data;
	};

}
