#include "WrongLoginPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// �����������
	CWrongLoginPacket::CWrongLoginPacket()
	{

	}

	// ����������
	CWrongLoginPacket::~CWrongLoginPacket()
	{

	}

	// �������� ID ������
	unsigned short int CWrongLoginPacket::getId() const
	{
		return 931;
	}

	// �������� ����� � �����
	void CWrongLoginPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(1001);
	}
}