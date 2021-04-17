#include "CreatePasswordPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// Конструктор
	CCreatePasswordPacket::CCreatePasswordPacket()
	{

	}

	// Деструктор
	CCreatePasswordPacket::~CCreatePasswordPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CCreatePasswordPacket::getId() const
	{
		return 941;
	}

	// Записать пакет в буфер
	void CCreatePasswordPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(534);
	}
}