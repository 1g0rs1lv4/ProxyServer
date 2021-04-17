#include "Account.h"

namespace PKO
{

	// Конструктор
	CAccount::CAccount() :
		m_login(""), m_password(""), m_mac_address(""),
		m_chap_string(""), m_bill_string(""), m_flag(0), m_version(0),
		m_encryption_key_length(0)
	{
		std::memset(m_encryption_key, 0x00, sizeof(m_encryption_key));
	}

	// Деструктор
	CAccount::~CAccount()
	{

	}

	// Установить поля
	void CAccount::setLogin(const std::string& login)
	{
		m_login = login;
	}

	void CAccount::setPassword(const std::string& password)
	{
		m_password = password;
	}

	void CAccount::setMacAddress(const std::string& mac_address)
	{
		m_mac_address = mac_address;
	}

	void CAccount::setChapString(const std::string& chap_string)
	{
		m_chap_string = chap_string;
	}

	void CAccount::setBillString(const std::string& bill_string)
	{
		m_bill_string = bill_string;
	}

	void CAccount::setFlag(unsigned short int flag)
	{
		m_flag = flag;
	}

	void CAccount::setVersion(unsigned short int version)
	{
		m_version = version;
	}

	void CAccount::setEncryptionKey(const char *key, 
												size_t length)
	{
		if (key == nullptr) {
			m_encryption_key_length = 0;
			std::memset(m_encryption_key, 0x00, sizeof(m_encryption_key));
		}
		else {
			m_encryption_key_length = length;
			std::memcpy(m_encryption_key, key, length);
		}
	}

	// Получить поля
	const std::string& CAccount::getLogin() const
	{
		return m_login;
	}

	const std::string& CAccount::getPassword() const
	{
		return m_password;
	}

	const std::string& CAccount::getMacAddress() const
	{
		return m_mac_address;
	}

	const std::string& CAccount::getChapString() const
	{
		return m_chap_string;
	}

	const std::string& CAccount::getBillString() const
	{
		return m_bill_string;
	}

	unsigned short int CAccount::getFlag() const
	{
		return m_flag;
	}

	unsigned short int CAccount::getVersion() const
	{
		return m_version;
	}

	const char *CAccount::getEncryptionKey() const
	{
		return m_encryption_key;
	}

	size_t CAccount::getEncryptionKeyLength() const
	{
		return m_encryption_key_length;
	}
}