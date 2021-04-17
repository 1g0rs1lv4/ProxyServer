#include "WrongLoginPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// Конструктор
	CWrongLoginPacket::CWrongLoginPacket()
	{

	}

	// Деструктор
	CWrongLoginPacket::~CWrongLoginPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CWrongLoginPacket::getId() const
	{
		return 931;
	}

	// Записать пакет в буфер
	void CWrongLoginPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(1001);
	}
}