#include "ServerPacketHandlerManager.h"
#include "PacketHandler/EnterMapHandler.h"
#include "PacketHandler/SetStallSuccessHandler.h"
#include "PacketHandler/ChapStringHandler.h"
#include "PacketHandler/PingHandler.h"
#include "PacketHandler/LoginResultHandler.h"
#include "PacketHandler/SetStallBuyHandler.h"
#include "PacketHandler/SysInfoHandler.h"
#include "PacketHandler/CActionHandler.h"
#include "PacketHandler/SynKitbagHandler.h"
#include "PacketHandler/GMNoticeHandler.h"
#include "PacketHandler/BeginSeeHandler.h"

namespace PKO
{
	CServerPacketHandlerManager::CServerPacketHandlerManager()
	{
		try
		{
			// Серверные модули
			this->attach(new CEnterMapHandler());
			this->attach(new CSetStallSuccessHandler());
			this->attach(new CChapStringHandler());
			this->attach(new CPingHandler());
			this->attach(new CLoginResultHandler());
			this->attach(new CSetStallBuyHandler());
			this->attach(new CActionHandler());
			this->attach(new CSynKitbagHandler());
			this->attach(new CGMNotice());
			// this->attach(new CSysInfoHandler());
			// Отображения статуса ларьков
			//this->attach(new CBeginSeeHandler());
		}
		catch (...) {

		}
	}


	CServerPacketHandlerManager::~CServerPacketHandlerManager()
	{

	}
}