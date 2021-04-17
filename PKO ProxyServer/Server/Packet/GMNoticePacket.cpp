#include "GMNoticePacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	CGMNoticePacket::CGMNoticePacket() :
		m_message("")
	{

	}

	CGMNoticePacket::~CGMNoticePacket()
	{

	}

	// Получить ID пакета
	unsigned short int CGMNoticePacket::getId() const
	{
		return 5400;
	}

	// Записать пакет в буфер
	void CGMNoticePacket::write(CBinaryWriter& Writer)
	{
		Writer.writeString("GM");
		Writer.writeString(m_message);
	}

	// Установить пакет
	void CGMNoticePacket::setMessage(const std::string& message)
	{
		m_message = message;
	}
}