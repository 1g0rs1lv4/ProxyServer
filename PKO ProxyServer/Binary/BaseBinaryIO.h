#pragma once
#include <string>
#include <stdexcept>
#include <WinSock2.h>

namespace PKO
{
	// Типы данных
	typedef unsigned char      ubyte_t;
	typedef unsigned short int uint16_t;
	typedef unsigned int       uint32_t;
	typedef std::string        string_t;

	// Тип относительной позиции курсора
	enum seek_type_t
	{
		seek_begin = 0,
		seek_cur = 1,
		seek_end = 2,
	};

	class binary_io_exception : public std::runtime_error
	{
		public:
			binary_io_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~binary_io_exception() { }
	};


	class CBaseBinaryIO
	{
		public:

			// Конструктор
			CBaseBinaryIO();
			CBaseBinaryIO(char *data, size_t size);

			// Деструктор
			~CBaseBinaryIO();

			// Получить размер данных
			size_t size() const;

			// Получить указатель на данные
			char *data() const;
			
			// Получить позицию курсора
			size_t tell() const;

			// Переместить курсор
			void seek(size_t newpos, seek_type_t type);

			// Установить данные
			void setData(char *data, size_t size);

			// Сколько места осталось в буфере
			size_t free() const;

			// Позиция курсора
			size_t pos() const;

		private:

			// Запретим копирование
			CBaseBinaryIO(const CBaseBinaryIO&) = delete;
			CBaseBinaryIO& operator=(const CBaseBinaryIO&) = delete;
		
		protected:

			// Проверить, что в буфере остались данные
			void checkSize(size_t n);
	
			// Размер данных
			size_t m_size;

			// Позиция курсора 
			size_t m_pos;

			// Указатель на данные
			char *m_data;

	};
}

