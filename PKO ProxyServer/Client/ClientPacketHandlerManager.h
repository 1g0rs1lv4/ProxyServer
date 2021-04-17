#pragma once
#include "../Main/PacketHandlerManager.h"

namespace PKO
{
	class CClientPacketHandlerManager : public CPacketHandlerManager
	{
		public:

			// Конструктор
			CClientPacketHandlerManager();

			// Деструктор
			~CClientPacketHandlerManager();
	};
}
