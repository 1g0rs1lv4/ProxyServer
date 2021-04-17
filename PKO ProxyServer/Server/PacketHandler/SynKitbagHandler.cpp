#include "SynKitbagHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"

namespace PKO
{

	//	Конструктор
	CSynKitbagHandler::CSynKitbagHandler() :
		m_cha_id(0), m_new_size(0)
	{

	}

	// Деструктор
	CSynKitbagHandler::~CSynKitbagHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CSynKitbagHandler::getId() const
	{
		return 551;
	}

	// Прочитать пакет
	void CSynKitbagHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_cha_id = Reader.readUint32();
		m_new_size = Reader.readUint16();
	}

	// Обработать пакет
	bool CSynKitbagHandler::handle(CPlayer& Player)
	{
		if (Player.character().getId() == m_cha_id) {
			Player.character().setKitbagSize(m_new_size);
		}

		return true;
	}

	// Сбросить обработчик
	void CSynKitbagHandler::reset()
	{
		m_cha_id = 0;
		m_new_size = 0;
	}

	// Действие после отправки пакета
	void CSynKitbagHandler::after_send(CPlayer& Player) {



	}

}