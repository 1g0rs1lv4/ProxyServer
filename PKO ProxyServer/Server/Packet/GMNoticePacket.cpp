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

	// �������� ID ������
	unsigned short int CGMNoticePacket::getId() const
	{
		return 5400;
	}

	// �������� ����� � �����
	void CGMNoticePacket::write(CBinaryWriter& Writer)
	{
		Writer.writeString("GM");
		Writer.writeString(m_message);
	}

	// ���������� �����
	void CGMNoticePacket::setMessage(const std::string& message)
	{
		m_message = message;
	}
}