#include "CreatePasswordPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// �����������
	CCreatePasswordPacket::CCreatePasswordPacket()
	{

	}

	// ����������
	CCreatePasswordPacket::~CCreatePasswordPacket()
	{

	}

	// �������� ID ������
	unsigned short int CCreatePasswordPacket::getId() const
	{
		return 941;
	}

	// �������� ����� � �����
	void CCreatePasswordPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(534);
	}
}