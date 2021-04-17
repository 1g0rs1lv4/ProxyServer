#include "BinaryWriter.h"

namespace PKO
{

	// Конструктор
	CBinaryWriter::CBinaryWriter() :
		CBaseBinaryIO()
	{

	}

	CBinaryWriter::CBinaryWriter(char *data, size_t size) :
		CBaseBinaryIO(data, size)
	{

	}

	// Деструктор
	CBinaryWriter::~CBinaryWriter()
	{

	}

	// Записать данные
	void CBinaryWriter::write(const ubyte_t *data, size_t n)
	{
		// Проверяем что в буфере есть место
		checkSize(n);

		// Копируем байты в буфер
		std::memcpy(m_data + m_pos, data, n);

		// Увеличиваем позицию записи
		m_pos += n;
	}

	// Записать байт
	void CBinaryWriter::writeByte(ubyte_t c)
	{
		write(reinterpret_cast<const ubyte_t *>(&c), sizeof(c));
	}

	// Записать UInt16
	void CBinaryWriter::writeUint16(uint16_t n)
	{
		n = htons(n);
		write(reinterpret_cast<const ubyte_t *>(&n), sizeof(n));
	}

	// Записать UInt32
	void CBinaryWriter::writeUint32(uint32_t n)
	{
		n = htonl(n);
		write(reinterpret_cast<const ubyte_t *>(&n), sizeof(n));
	}

	// Записать строку
	void CBinaryWriter::writeString(const string_t& String)
	{
		// Пишем размер строки
		size_t length = String.length() + 1;
		writeUint16(static_cast<uint16_t>(length));

		// Пишем строку
		write(reinterpret_cast<const ubyte_t *>(String.c_str()), length);
	}

	// Записать массив байт
	void CBinaryWriter::writeByteArray(ubyte_t *buffer, size_t count)
	{
		write(buffer, count);
	}

}