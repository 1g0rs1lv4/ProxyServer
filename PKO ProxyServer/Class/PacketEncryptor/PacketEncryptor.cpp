#include <memory>
#include "../PacketEncryptor/PacketEncryptor.h"
#include "../PacketEncoder/PacketEncoder.h"
#include "../DES/DES.h"

namespace PKO
{
	// Конструктор
	CPacketEncryptor::CPacketEncryptor() :
		m_enabled(false), m_session_key_length(0)
	{
		std::memset(m_session_key, 0x00, sizeof(m_session_key));
		std::memset(m_keys[0], 0x00, sizeof(m_keys[0]));
		std::memset(m_keys[1], 0x00, sizeof(m_keys[1]));
		std::memset(m_keys[2], 0x00, sizeof(m_keys[2]));
		std::memset(m_keys[3], 0x00, sizeof(m_keys[3]));
	}

	// Деструткор
	CPacketEncryptor::~CPacketEncryptor()
	{

	}

	// Включено ли шифрование
	bool CPacketEncryptor::enabled() const
	{
		return m_enabled;
	}

	// Инициализировать шифрование
	// Установить поля
	void CPacketEncryptor::init(bool enabled, const CAccount& account)
	{
		m_enabled = enabled;
		if (m_enabled)
		{
			unsigned short int version = account.getVersion();
			const std::string chap_string = account.getChapString();
			const std::string password = account.getPassword();
			char *key = const_cast<char *>(account.getEncryptionKey());
			size_t key_length = account.getEncryptionKeyLength();
			short int key_data = version * version * 0x1232222;
			int noise = key_data * int(*(int*)(chap_string.c_str() + chap_string.length() - 4));

			// Ключ сессии
			CDES::RunDes(CDES::DECRYPT, CDES::ECB, key, m_session_key, key_length, password.c_str(), static_cast<unsigned char>(password.length()));
			m_session_key_length = 6;

			// Инициализируем ключи для шифрования пакетов
			CPacketEncoder::init_Noise(noise, m_keys[0]);
			CPacketEncoder::init_Noise(noise, m_keys[1]);
			CPacketEncoder::init_Noise(noise, m_keys[2]);
			CPacketEncoder::init_Noise(noise, m_keys[3]);
		}
		else
		{
			std::memset(m_session_key, 0x00, sizeof(m_session_key));
			m_session_key_length = 0;
		}
	}

	// Зашифровать пакет
	void CPacketEncryptor::encrypt(char *data, 
						size_t length, encrypt_t type)
	{
		//printf("* encrypt length = %i\n", length);
		char *key = nullptr;
		switch (type)
		{
			case encrypt_t::enc_cs:
				key = m_keys[2];
				break;

			case encrypt_t::enc_sc:
				key = m_keys[3];
				break;
		}

		CPacketEncoder::encrypt_Noise(key, data, length);
		CPacketEncoder::encrypt_B(data, length, m_session_key, m_session_key_length, true);
	}

	// Расшифровать пакет
	void CPacketEncryptor::decrypt(char *data, size_t length, decrypt_t type)
	{
		//printf("* decrypt length = %i\n", length);
		char *key = nullptr;
		switch (type)
		{
			case decrypt_t::dec_cs:
				key = m_keys[0];
				break;

			case decrypt_t::dec_sc:
				key = m_keys[1];
				break;
		}
		CPacketEncoder::encrypt_B(data, length, m_session_key, m_session_key_length, false);
		CPacketEncoder::decrypt_Noise(key, data, length);
	}
}