#include "UpdatePasswordPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// Конструктор
	CUpdatePasswordPacket::CUpdatePasswordPacket()
	{

	}

	// Деструктор
	CUpdatePasswordPacket::~CUpdatePasswordPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CUpdatePasswordPacket::getId() const
	{
		return 942;
	}

	// Записать пакет в буфер
	void CUpdatePasswordPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(534);
	}
}