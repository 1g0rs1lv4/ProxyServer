#include "NewChaHandle.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include <iostream>
#include "../../Server/Packet/WrongNewChaPacket.h"
#include <sstream>

namespace PKO
{
	// Конструктор
	CNewChaHandle::CNewChaHandle() : chaname(""), birth(""), len(0)
	{
		reset();
	}

	// Деструктор
	CNewChaHandle::~CNewChaHandle()
	{

	}

	// Получить ID пакета
	unsigned short int CNewChaHandle::getId() const
	{
		return 435;
	}

	// Прочитать пакет
	void CNewChaHandle::read(CBinaryReader& Reader, CPlayer& Player)
	{
		chaname = Reader.readString();
		birth = Reader.readString();
		len = Reader.readUint16();
		if (len == sizeof(LOOK))
		{
			Reader.readByteArray(reinterpret_cast<ubyte_t*>(&look), len);
		}
	}

	// Обработать пакет
	bool CNewChaHandle::handle(CPlayer& Player)
	{
		for (unsigned int i = 0; i < enumEQUIP_NUM; i++)
		{
			for (unsigned int s = 0; s < defITEM_INSTANCE_ATTR_NUM; s++)
			{
				if (look.SLink[i].sInstAttr[s][0] != 0 || look.SLink[i].sInstAttr[s][1] != 0)
				{
					std::stringstream message;
					message << "bad character look ([" << i << "] ID: " << look.SLink[i].sID << " | PARAMS: [" << look.SLink[i].sInstAttr[s][0] << "," << look.SLink[i].sInstAttr[s][0] << "])";
					Player.sendDebug(message.str());
					CWrongNewChaPacket wrong_newcha(520);
					Player.sendPacket(Player.server(), &wrong_newcha);

					return false;
				}
			}
		}
		return true;
	}

	// Сбросить обработчик
	void CNewChaHandle::reset()
	{
		chaname = "";
		birth = "";
		len = 0;
	}

	// Действие после отправки пакета
	void CNewChaHandle::after_send(CPlayer& Player) {



	}

}