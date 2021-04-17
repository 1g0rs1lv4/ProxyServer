#include "Protection.h"

namespace PKO
{
	// Конструктор
	CProtection::CProtection() : 
		m_enabled(false), m_packet_counter(0), m_ver(0)
	{

	}

	// Деструктор
	CProtection::~CProtection()
	{

	}

	// Инициализировать защиту
	void CProtection::init(bool enabled, unsigned short int ver)
	{
		m_enabled = enabled;
		m_packet_counter = 0;
		m_ver = ver;
	}

	// Проверить пакет
	bool CProtection::check_packet(unsigned int n)
	{
		if (m_enabled)
		{
			if (m_packet_counter != n) {
				return false;
			}

			m_packet_counter++;
		}

		return true;
	}

	// Включена ли защита
	bool CProtection::enabled() const
	{
		return m_enabled;
	}

}

