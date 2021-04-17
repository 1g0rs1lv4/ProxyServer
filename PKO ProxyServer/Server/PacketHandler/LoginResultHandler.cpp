#include "LoginResultHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <sstream>

namespace PKO
{
	// �����������
	CLoginResultHandler::CLoginResultHandler() : 
		m_result(0), m_comm_encryption(false), m_encryption_key_length(0)
	{
		std::memset(m_encryption_key, 0x00, sizeof(m_encryption_key));
	}

	// ����������
	CLoginResultHandler::~CLoginResultHandler()
	{

	}

	// �������� ID ������
	unsigned short int CLoginResultHandler::getId() const
	{
		return 931;
	}

	// ��������� �����
	void CLoginResultHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_result = Reader.readUint16();
		if (m_result == result_t::result_success)
		{
			m_encryption_key_length = Reader.readUint16();
			Reader.readByteArray(reinterpret_cast<ubyte_t *>(m_encryption_key), m_encryption_key_length);
			Reader.seek(8, seek_type_t::seek_end);
			m_comm_encryption = static_cast<bool>(Reader.readUint32());
		}
	}

	// ���������� �����
	bool CLoginResultHandler::handle(CPlayer& Player)
	{

		if (m_result == result_t::result_success)
		{
			if (m_comm_encryption)
			{
				Player.account().setEncryptionKey(m_encryption_key, m_encryption_key_length);
			}

			Player.packet_encryptor().init(m_comm_encryption, Player.account());

			Player.on_server_login();
		}
		return true;
	}

	// �������� ����������
	void CLoginResultHandler::reset()
	{
		m_result = 0;
		m_comm_encryption = false;
		m_encryption_key_length = 0;

		std::memset(m_encryption_key, 0x00, sizeof(m_encryption_key));
	}

	// �������� ����� �������� ������
	void CLoginResultHandler::after_send(CPlayer& Player) {



	}

}