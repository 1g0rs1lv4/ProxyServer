#include "UpdatePasswordPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// �����������
	CUpdatePasswordPacket::CUpdatePasswordPacket()
	{

	}

	// ����������
	CUpdatePasswordPacket::~CUpdatePasswordPacket()
	{

	}

	// �������� ID ������
	unsigned short int CUpdatePasswordPacket::getId() const
	{
		return 942;
	}

	// �������� ����� � �����
	void CUpdatePasswordPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(534);
	}
}