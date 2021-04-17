#pragma once
#include "../Main/PacketHandlerManager.h"

namespace PKO
{
	class CServerPacketHandlerManager : public CPacketHandlerManager
	{
		public:

			// Конструктор
			CServerPacketHandlerManager();

			// Деструктор
			virtual ~CServerPacketHandlerManager();
	};
}

