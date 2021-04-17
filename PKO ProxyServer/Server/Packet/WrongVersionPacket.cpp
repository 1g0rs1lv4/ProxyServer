#include "WrongVersionPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// �����������
	CWrongVersionPacket::CWrongVersionPacket()
	{

	}

	// ����������
	CWrongVersionPacket::~CWrongVersionPacket()
	{

	}

	// �������� ID ������
	unsigned short int CWrongVersionPacket::getId() const
	{
		return 931;
	}

	// �������� ����� � �����
	void CWrongVersionPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(7);
	}
}