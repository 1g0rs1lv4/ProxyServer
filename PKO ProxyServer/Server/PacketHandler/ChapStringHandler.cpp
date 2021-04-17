#include "ChapStringHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// �����������
	CChapStringHandler::CChapStringHandler() :
		m_chap_string("")
	{

	}

	// ����������
	CChapStringHandler::~CChapStringHandler()
	{

	}

	// �������� ID ������
	unsigned short int CChapStringHandler::getId() const
	{
		return 940;
	}

	// ��������� �����
	void CChapStringHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_chap_string = Reader.readString();
	}

	// ���������� �����
	bool CChapStringHandler::handle(CPlayer& Player)
	{
		Player.account().setChapString(m_chap_string);
		return true;
	}

	// �������� ����������
	void CChapStringHandler::reset()
	{
		m_chap_string = "";
	}

	// �������� ����� �������� ������
	void CChapStringHandler::after_send(CPlayer& Player) {



	}

}