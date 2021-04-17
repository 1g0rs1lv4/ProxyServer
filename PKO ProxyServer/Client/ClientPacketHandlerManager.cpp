#include "ClientPacketHandlerManager.h"
#include "../Client/PacketHandler/AccountLoginHandler.h"
#include "../Client/PacketHandler/SetStallCloseHandler.h"
#include "../Client/PacketHandler/DisconnectHandler.h"
#include "../Client/PacketHandler/SetStallInfoHandler.h"
#include "../Client/PacketHandler/CreatePasswordHandler.h"
#include "../Client/PacketHandler/ChangePasswordHandler.h"
#include "../Client/PacketHandler/NewChaHandle.h"
//#include "../Client/PacketHandler/EndPlayHandler.h"
//#include "../Client/PacketHandler/BeginPlayHandler.h"

namespace PKO
{
	// �����������
	CClientPacketHandlerManager::CClientPacketHandlerManager()
	{
		try
		{
			// ���������� ������
			this->attach(new CAccountLoginHandler());
			this->attach(new CSetStallCloseHandler());
			this->attach(new CDisconnectHandler());
			this->attach(new CSetStallInfoHandler());
			this->attach(new CCreatePasswordHandler());
			this->attach(new �ChangePasswordHandler());
			this->attach(new CNewChaHandle());

			
		}
		catch (...) {

		}
	}

	// ����������
	CClientPacketHandlerManager::~CClientPacketHandlerManager()
	{

	}
}