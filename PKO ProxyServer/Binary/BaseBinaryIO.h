#pragma once
#include <string>
#include <stdexcept>
#include <WinSock2.h>

namespace PKO
{
	// ���� ������
	typedef unsigned char      ubyte_t;
	typedef unsigned short int uint16_t;
	typedef unsigned int       uint32_t;
	typedef std::string        string_t;

	// ��� ������������� ������� �������
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

			// �����������
			CBaseBinaryIO();
			CBaseBinaryIO(char *data, size_t size);

			// ����������
			~CBaseBinaryIO();

			// �������� ������ ������
			size_t size() const;

			// �������� ��������� �� ������
			char *data() const;
			
			// �������� ������� �������
			size_t tell() const;

			// ����������� ������
			void seek(size_t newpos, seek_type_t type);

			// ���������� ������
			void setData(char *data, size_t size);

			// ������� ����� �������� � ������
			size_t free() const;

			// ������� �������
			size_t pos() const;

		private:

			// �������� �����������
			CBaseBinaryIO(const CBaseBinaryIO&) = delete;
			CBaseBinaryIO& operator=(const CBaseBinaryIO&) = delete;
		
		protected:

			// ���������, ��� � ������ �������� ������
			void checkSize(size_t n);
	
			// ������ ������
			size_t m_size;

			// ������� ������� 
			size_t m_pos;

			// ��������� �� ������
			char *m_data;

	};
}

