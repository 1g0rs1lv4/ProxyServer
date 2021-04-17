#include "PopupNoticePacket.h"
#include "../../Binary/BinaryWriter.h"

namespace PKO
{
	CPopupNoticePacket::CPopupNoticePacket(const std::string& message) :
		m_message("")
	{
		m_message = message;
	}

	CPopupNoticePacket::~CPopupNoticePacket()
	{
		
	}

	// Получить ID пакета
	unsigned short int CPopupNoticePacket::getId() const
	{
		return 568;
	}

	// Записать пакет в буфер
	void CPopupNoticePacket::write(CBinaryWriter& Writer)
	{
		Writer.writeString(m_message);
	}

}