#include "LoginPacket.h"
#include "../../Binary/BinaryWriter.h"
#include "../../Class/PasswordEncoder/PasswordEncoder.h"
#pragma warning(disable:4996)

namespace PKO
{
	// Конструктор
	CLoginPacket::CLoginPacket() : m_nobill(""), m_login(""), m_password(""), m_mac_address(""),
		m_flag(0), m_version(0), m_chap_string(""), m_ip_address("")
	{

	}

	// Деструктор
	CLoginPacket::~CLoginPacket()
	{

	}

	// Получить ID пакета
	unsigned short int CLoginPacket::getId() const
	{
		return 431;
	}

	// Записать пакет в буфер
	void CLoginPacket::write(CBinaryWriter& Writer)
	{
		CPasswordEncoder Encoder;
		ubyte_t password[128];
		unsigned short int length = 0;

		// Шифруем пароль
		Encoder.set_password(m_password);
		Encoder.set_chap_string(m_chap_string);
		Encoder.encode(reinterpret_cast<char *>(password), length);

		// Записываем пакет
		Writer.writeString(m_nobill);
		Writer.writeString(m_login);
		Writer.writeUint16(length);
		Writer.writeByteArray(password, length);
		Writer.writeString(m_mac_address);
		Writer.writeUint32(inet_addr(m_ip_address.c_str()));
		Writer.writeUint16(m_flag);
		Writer.writeUint16(m_version);
	}

	// Установить поля
	void CLoginPacket::setNobill(const std::string& nobill)
	{
		m_nobill = nobill;
	}

	void CLoginPacket::setLogin(const std::string& login)
	{
		m_login = login;
	}

	void CLoginPacket::setPassword(const std::string& password)
	{
		m_password = password;
	}

	void CLoginPacket::setMacAddress(const std::string& mac_address)
	{
		m_mac_address = mac_address;
	}

	void CLoginPacket::setIpAddress(const std::string& ip_address)
	{
		m_ip_address = ip_address;
	}

	void CLoginPacket::setChapString(const std::string& chap_string)
	{
		m_chap_string = chap_string;
	}

	void CLoginPacket::setFlag(unsigned short int flag)
	{
		m_flag = flag;
	}

	void CLoginPacket::setVersion(unsigned short int version)
	{
		m_version = version;
	}

}