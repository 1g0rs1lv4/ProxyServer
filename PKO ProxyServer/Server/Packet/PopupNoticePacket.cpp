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

	// �������� ID ������
	unsigned short int CPopupNoticePacket::getId() const
	{
		return 568;
	}

	// �������� ����� � �����
	void CPopupNoticePacket::write(CBinaryWriter& Writer)
	{
		Writer.writeString(m_message);
	}

}