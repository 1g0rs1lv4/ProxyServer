#include "SynKitbagHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"

namespace PKO
{

	//	�����������
	CSynKitbagHandler::CSynKitbagHandler() :
		m_cha_id(0), m_new_size(0)
	{

	}

	// ����������
	CSynKitbagHandler::~CSynKitbagHandler()
	{

	}

	// �������� ID ������
	unsigned short int CSynKitbagHandler::getId() const
	{
		return 551;
	}

	// ��������� �����
	void CSynKitbagHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_cha_id = Reader.readUint32();
		m_new_size = Reader.readUint16();
	}

	// ���������� �����
	bool CSynKitbagHandler::handle(CPlayer& Player)
	{
		if (Player.character().getId() == m_cha_id) {
			Player.character().setKitbagSize(m_new_size);
		}

		return true;
	}

	// �������� ����������
	void CSynKitbagHandler::reset()
	{
		m_cha_id = 0;
		m_new_size = 0;
	}

	// �������� ����� �������� ������
	void CSynKitbagHandler::after_send(CPlayer& Player) {



	}

}