#include <memory>
#include "NetBuffer.h"


namespace PKO
{
	// Конструктор
	CNetBuffer::CNetBuffer(size_t size) :
		m_size(size), m_length(0)
	{
		// Создаем буфер
		m_data = new char[size];
		std::memset(m_data, 0x00, size);
	}

	// Деструктор
	CNetBuffer::~CNetBuffer()
	{
		// Удаляем буфер
		if (m_data != nullptr) {
			delete[] m_data;
		}

		m_size = 0;
	}

	// Добавить данные в буфер
	void CNetBuffer::add(const char *data, size_t length)
	{
		std::memcpy(m_data + m_length, data, length);
		m_length += length;
	}

	// Удалить данные из буфера
	void CNetBuffer::remove(size_t length)
	{
		m_length -= length;
		std::memcpy(m_data, m_data + length, m_length);
	}

	// Очистить буфер
	void CNetBuffer::clear()
	{
		std::memset(m_data, 0x00, m_length);
		m_length = 0;
	}

	// Получить указатель на данные
	const char *CNetBuffer::data() const
	{
		return m_data;
	}

	// Получить размер буфера
	size_t CNetBuffer::size() const
	{
		return m_size;
	}

	// Получить длину буфера
	size_t CNetBuffer::length() const
	{
		return m_length;
	}

	// Установить длину буфера
	void CNetBuffer::set_length(size_t length)
	{
		if (length > m_size) {
			length = m_size;
		}

		m_length = length;
	}
}