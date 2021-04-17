#include "GMNoticeHandler.h"
#include "../Packet/GMNoticePacket.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// Конструктор
	CGMNotice::CGMNotice()
		: m_message("")
	{

	}

	// Деструктор
	CGMNotice::~CGMNotice()
	{

	}

	// Получить ID пакета
	unsigned short int CGMNotice::getId() const
	{
		return 780;
	}

	// Прочитать пакет
	void CGMNotice::read(CBinaryReader& Reader, CPlayer& Player)
	{
		// Считаем полученное гм сообщение
		m_message = Reader.readString();
	}

	// Обработать пакет
	bool CGMNotice::handle(CPlayer& Player)
	{
		
		// Сформируем пакет ГМ сообщения для клиента
		CGMNoticePacket notice_packet;
		notice_packet.setMessage(m_message);

		// Разошлем всем ГМ сообщение
		const player_list_t& players = Player.stall_server()->getPlayers();
		auto i = players.begin();
		while (i != players.end())
		{
			CPlayer* ply = *i;
			if (ply->server()->connected()) {
				ply->sendPacket(ply->server(), &notice_packet);
			}

			i++;
		}

		return true;
	}

	// Сбросить обработчик
	void CGMNotice::reset()
	{

	}

	// Действие после отправки пакета
	void CGMNotice::after_send(CPlayer& Player) {



	}

}