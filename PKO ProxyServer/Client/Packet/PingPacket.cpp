#include "PingPacket.h"

namespace PKO
{
	// Конструктор
	CPingPacket::CPingPacket()
	{

	}

	// Деструктор
	CPingPacket::~CPingPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CPingPacket::getId() const
	{
		return 17;
	}

	// Записать пакет в буфер
	void CPingPacket::write(CBinaryWriter& Writer)
	{

	}
}