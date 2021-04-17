#include "BinaryReader.h"

namespace PKO
{

	// �����������
	CBinaryReader::CBinaryReader() :
		CBaseBinaryIO()
	{

	}

	CBinaryReader::CBinaryReader(char *data, size_t size) :
		CBaseBinaryIO(data,  size)
	{

	}

	// ����������
	CBinaryReader::~CBinaryReader()
	{

	}

	// ��������� ������
	void CBinaryReader::read(ubyte_t *dst, size_t n)
	{
		// ��������� ��� � ������ ���� n ����
		checkSize(n);

		// �������� count ���� � ��������
		std::memcpy(dst, m_data + m_pos, n);

		// ����������� ������� ������
		m_pos += n;
	}

	// ��������� ����
	ubyte_t CBinaryReader::readByte()
	{
		char b;
		read(reinterpret_cast<ubyte_t *>(&b), sizeof(b));

		return b;
	}

	// ��������� UInt16
	uint16_t CBinaryReader::readUint16()
	{
		unsigned short int n;
		read(reinterpret_cast<ubyte_t *>(&n), sizeof(n));

		return ntohs(n);
	}

	// ��������� UInt32
	uint32_t CBinaryReader::readUint32()
	{
		unsigned int n;
		read(reinterpret_cast<ubyte_t *>(&n), sizeof(n));

		return ntohl(n);
	}

	// ��������� ������
	string_t CBinaryReader::readString()
	{
		// ���� ������
		std::string str;

		// ������ ����� ������
		unsigned short int n = readUint16();

		// ��������� ��� � ������ ���� ������
		checkSize(n);

		// ����������� ����� ��� ������
		str.reserve(n);

		// ������ ������
		str.append(m_data + m_pos, n - 1);

		// ����������� ������� ������
		m_pos += n;

		return str;
	}

	// ��������� ������ ����
	void CBinaryReader::readByteArray(ubyte_t *dst, size_t count)
	{
		read(dst, count);
	}
}
