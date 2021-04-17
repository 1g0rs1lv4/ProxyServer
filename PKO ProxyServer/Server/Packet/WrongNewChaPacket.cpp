#include "WrongNewChaPacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	// Конструктор
	CWrongNewChaPacket::CWrongNewChaPacket(unsigned short int error)
	{
		error_id = error;
	}

	// Деструктор
	CWrongNewChaPacket::~CWrongNewChaPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CWrongNewChaPacket::getId() const
	{
		return 935;
	}

	// Записать пакет в буфер
	void CWrongNewChaPacket::write(CBinaryWriter& Writer)
	{
		Writer.writeUint16(error_id);
	}
}