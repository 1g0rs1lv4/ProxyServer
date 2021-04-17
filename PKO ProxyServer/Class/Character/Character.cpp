#include "Character.h"


namespace PKO
{
	// Конструктор
	CCharacter::CCharacter() :
		m_cha_id(0), m_cha_name(""), m_map_name(""),
		m_pos_x(0), m_pos_y(0), m_kitbag_size(0), m_gm(0)
	{
		// Зарезервируем место для 48 ячеек инвентаря
		m_kitbag.reserve(MAX_KITBAG_SIZE);
	}

	// Деструктор
	CCharacter::~CCharacter()
	{

	}

	// Установим гм уровень
	void CCharacter::setGm(const char lv)
	{
		m_gm = lv;
	}

	// Получить поля
	void CCharacter::setId(unsigned int cha_id)
	{
		m_cha_id = cha_id;
	}

	void CCharacter::setName(const std::string& cha_name)
	{
		m_cha_name = cha_name;
	}

	void CCharacter::setMap(const std::string& map_name)
	{
		m_map_name = map_name;
	}

	void CCharacter::setPos(unsigned int x, unsigned int y)
	{
		m_pos_x = x;
		m_pos_y = y;
	}


	// Установить поля
	unsigned int CCharacter::getId() const
	{
		return m_cha_id;
	}

	const std::string& CCharacter::getName() const
	{
		return m_cha_name;
	}

	const std::string& CCharacter::getMap() const
	{
		return m_map_name;
	}

	CSetStall& CCharacter::stall()
	{
		return m_stall;
	}

	unsigned int CCharacter::getPosX() const
	{
		return m_pos_x;
	}

	unsigned int CCharacter::getPosY() const
	{
		return m_pos_y;
	}

	// Получить инвентарь
	std::vector<SKitbagGrid>& CCharacter::kitbag()
	{
		return m_kitbag;
	}

	// Установить размер инвентаря
	void CCharacter::setKitbagSize(unsigned int size)
	{
		if (size > MAX_KITBAG_SIZE) {
			size = MAX_KITBAG_SIZE;
		}

		m_kitbag_size = size;
	}

	// Получить размер инвентаря
	unsigned int CCharacter::getKitbagSize() const
	{
		return m_kitbag_size;
	}

	// В Хаосе ли Игрок
	bool CCharacter::IsPKSilver() const {

		return strcmp("garner2", m_cha_name.c_str()) == 0;

	}

}