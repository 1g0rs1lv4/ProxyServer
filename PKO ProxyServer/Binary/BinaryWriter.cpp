#include "BinaryWriter.h"

namespace PKO
{

	// �����������
	CBinaryWriter::CBinaryWriter() :
		CBaseBinaryIO()
	{

	}

	CBinaryWriter::CBinaryWriter(char *data, size_t size) :
		CBaseBinaryIO(data, size)
	{

	}

	// ����������
	CBinaryWriter::~CBinaryWriter()
	{

	}

	// �������� ������
	void CBinaryWriter::write(const ubyte_t *data, size_t n)
	{
		// ��������� ��� � ������ ���� �����
		checkSize(n);

		// �������� ����� � �����
		std::memcpy(m_data + m_pos, data, n);

		// ����������� ������� ������
		m_pos += n;
	}

	// �������� ����
	void CBinaryWriter::writeByte(ubyte_t c)
	{
		write(reinterpret_cast<const ubyte_t *>(&c), sizeof(c));
	}

	// �������� UInt16
	void CBinaryWriter::writeUint16(uint16_t n)
	{
		n = htons(n);
		write(reinterpret_cast<const ubyte_t *>(&n), sizeof(n));
	}

	// �������� UInt32
	void CBinaryWriter::writeUint32(uint32_t n)
	{
		n = htonl(n);
		write(reinterpret_cast<const ubyte_t *>(&n), sizeof(n));
	}

	// �������� ������
	void CBinaryWriter::writeString(const string_t& String)
	{
		// ����� ������ ������
		size_t length = String.length() + 1;
		writeUint16(static_cast<uint16_t>(length));

		// ����� ������
		write(reinterpret_cast<const ubyte_t *>(String.c_str()), length);
	}

	// �������� ������ ����
	void CBinaryWriter::writeByteArray(ubyte_t *buffer, size_t count)
	{
		write(buffer, count);
	}

}