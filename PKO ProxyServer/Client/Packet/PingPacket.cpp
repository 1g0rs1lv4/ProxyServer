#include "PingPacket.h"

namespace PKO
{
	// �����������
	CPingPacket::CPingPacket()
	{

	}

	// ����������
	CPingPacket::~CPingPacket()
	{

	}

	// �������� ID ������
	unsigned short int CPingPacket::getId() const
	{
		return 17;
	}

	// �������� ����� � �����
	void CPingPacket::write(CBinaryWriter& Writer)
	{

	}
}