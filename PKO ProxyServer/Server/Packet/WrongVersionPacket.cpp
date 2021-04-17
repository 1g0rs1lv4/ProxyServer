#include "WrongVersionPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// Конструктор
	CWrongVersionPacket::CWrongVersionPacket()
	{

	}

	// Деструктор
	CWrongVersionPacket::~CWrongVersionPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CWrongVersionPacket::getId() const
	{
		return 931;
	}

	// Записать пакет в буфер
	void CWrongVersionPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(7);
	}
}