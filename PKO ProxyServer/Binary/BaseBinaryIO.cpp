#include "BaseBinaryIO.h"

namespace PKO
{
	// �����������
	CBaseBinaryIO::CBaseBinaryIO() :
		m_size(0), m_pos(0), m_data(nullptr)
	{

	}

	CBaseBinaryIO::CBaseBinaryIO(char *data, size_t size) :
		m_size(size), m_pos(0), m_data(data)
	{

	}

	// ����������
	CBaseBinaryIO::~CBaseBinaryIO()
	{

	}

	// �������� ������ ������
	size_t CBaseBinaryIO::size() const
	{
		return m_size;
	}

	// �������� ��������� �� ������
	char *CBaseBinaryIO::data() const
	{
		return m_data;
	}

	// �������� ������� �������
	size_t CBaseBinaryIO::tell() const
	{
		return m_pos;
	}

	// ����������� ������
	void CBaseBinaryIO::seek(size_t newpos, seek_type_t type)
	{
		// ��������� ����� ������� 
		if ( ((type == seek_begin || type == seek_end) && m_pos > m_size) ||
			(type == seek_cur && (m_pos + newpos) > m_size) )
		{
			throw binary_io_exception("New position is greater than buffer size! Current position: " + std::to_string(m_pos) + "; New position: " + std::to_string(newpos) + "; Mode: " + std::to_string(static_cast<int>(type)));
		}

		// ������������� ������� ������
		switch (type)
		{
			case seek_begin:
				m_pos = newpos;
				break;

			case seek_cur:
				m_pos += newpos;
				break;

			case seek_end:
				m_pos = m_size - newpos;
				break;
		}
	}

	// ���������� ������
	void CBaseBinaryIO::setData(char *data, size_t size)
	{
		m_data = data;
		m_size = size;
		m_pos = 0;
	}

	// ���������, ��� � ������ �������� ������
	void CBaseBinaryIO::checkSize(size_t n)
	{
		if ((m_pos + n) > m_size + 1) {
			throw binary_io_exception("No data available in the buffer! Read position: " + std::to_string(m_pos) + "; n: " + std::to_string(n));
		}
	}

	// ������� ����� �������� � ������
	size_t CBaseBinaryIO::free() const
	{
		return (m_size + 1) - m_pos;
	}

	// ������� �������
	size_t CBaseBinaryIO::pos() const {

		return m_pos;

	}

}