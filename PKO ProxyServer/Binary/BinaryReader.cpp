#include "BinaryReader.h"

namespace PKO
{

	// Конструткор
	CBinaryReader::CBinaryReader() :
		CBaseBinaryIO()
	{

	}

	CBinaryReader::CBinaryReader(char *data, size_t size) :
		CBaseBinaryIO(data,  size)
	{

	}

	// Деструктор
	CBinaryReader::~CBinaryReader()
	{

	}

	// Прочитать данные
	void CBinaryReader::read(ubyte_t *dst, size_t n)
	{
		// Проверяем что в буфере есть n байт
		checkSize(n);

		// Копируем count байт в приемник
		std::memcpy(dst, m_data + m_pos, n);

		// Увеличиваем позицию чтения
		m_pos += n;
	}

	// Прочитать байт
	ubyte_t CBinaryReader::readByte()
	{
		char b;
		read(reinterpret_cast<ubyte_t *>(&b), sizeof(b));

		return b;
	}

	// Прочитать UInt16
	uint16_t CBinaryReader::readUint16()
	{
		unsigned short int n;
		read(reinterpret_cast<ubyte_t *>(&n), sizeof(n));

		return ntohs(n);
	}

	// Прочитать UInt32
	uint32_t CBinaryReader::readUint32()
	{
		unsigned int n;
		read(reinterpret_cast<ubyte_t *>(&n), sizeof(n));

		return ntohl(n);
	}

	// Прочитать строку
	string_t CBinaryReader::readString()
	{
		// Наша строка
		std::string str;

		// Читаем длину строки
		unsigned short int n = readUint16();

		// Проверяем что в буфере есть данные
		checkSize(n);

		// Резервируем место под строку
		str.reserve(n);

		// Читаем строку
		str.append(m_data + m_pos, n - 1);

		// Увеличиваем позицию чтения
		m_pos += n;

		return str;
	}

	// Прочитать массив байт
	void CBinaryReader::readByteArray(ubyte_t *dst, size_t count)
	{
		read(dst, count);
	}
}
