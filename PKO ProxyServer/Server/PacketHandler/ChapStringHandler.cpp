#include "ChapStringHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// Конструктор
	CChapStringHandler::CChapStringHandler() :
		m_chap_string("")
	{

	}

	// Деструктор
	CChapStringHandler::~CChapStringHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CChapStringHandler::getId() const
	{
		return 940;
	}

	// Прочитать пакет
	void CChapStringHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_chap_string = Reader.readString();
	}

	// Обработать пакет
	bool CChapStringHandler::handle(CPlayer& Player)
	{
		Player.account().setChapString(m_chap_string);
		return true;
	}

	// Сбросить обработчик
	void CChapStringHandler::reset()
	{
		m_chap_string = "";
	}

	// Действие после отправки пакета
	void CChapStringHandler::after_send(CPlayer& Player) {



	}

}