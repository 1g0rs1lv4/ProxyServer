#include "WrongNewChaPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// �����������
	CWrongNewChaPacket::CWrongNewChaPacket(unsigned short int error)
	{
		error_id = error;
	}

	// ����������
	CWrongNewChaPacket::~CWrongNewChaPacket()
	{

	}

	// �������� ID ������
	unsigned short int CWrongNewChaPacket::getId() const
	{
		return 935;
	}

	// �������� ����� � �����
	void CWrongNewChaPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(error_id);
	}
}