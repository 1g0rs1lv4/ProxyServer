#include "PasswordEncoder.h"
#include "../DES/DES.h"

namespace PKO
{
	// Конструктор
	CPasswordEncoder::CPasswordEncoder() :
		m_chap_string(""), m_password("")
	{

	}

	// Деструктор
	CPasswordEncoder::~CPasswordEncoder()
	{

	}

	// Установить пароль и время подключения
	void CPasswordEncoder::set_password(const std::string& password)
	{
		m_password = password;
	}

	void CPasswordEncoder::set_chap_string(const std::string& chap_string)
	{
		m_chap_string = chap_string;
	}

	// Получить пароль и время подключения
	const std::string& CPasswordEncoder::get_password() const
	{
		return m_password;
	}

	const std::string& CPasswordEncoder::get_chap_stirng() const
	{
		return m_chap_string;
	}

	// Зашифровать пароль
	void CPasswordEncoder::encode(char *encoded_password, unsigned short int &length)
	{
		const char *src = m_chap_string.c_str();
		int src_len = m_chap_string.length();
		char szPad[200] = { 0 };
		unsigned int uiPadLen = sizeof(szPad);

		CDES::RunPad(CDES::PAD_ISO_1, src, src_len, szPad, uiPadLen);
		CDES::RunDes(CDES::ENCRYPT, CDES::ECB, szPad, encoded_password, uiPadLen, m_password.c_str(), static_cast<unsigned char>(m_password.length()));
	
		length = uiPadLen;
	}
}