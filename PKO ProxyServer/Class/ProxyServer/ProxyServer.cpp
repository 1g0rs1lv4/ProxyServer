//#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <event2\listener.h>
#include "ProxyServer.h"
#include "../Utils/Utils.h"
#include "../../Socket/callback.h"
#include "../../Pool/PlayerMaker.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/DisconnectPacket.h"

// �������������� ��� ������
#include "../../Class/WebServer/httplib.h"
#include "../../Class/WebServer/json.hpp"

// ���������� ������ �� ���������
#include "../../Protect/Protect.h"

// ���������� �������
extern HANDLE handle;

// ���������� ������
extern void WriteColorText(HANDLE handle, std::string str, WORD color);

namespace Module {

	#if ModuleWeb

		// ��������� WebServer
	void WebStart(PKO::CProxyServer* server) {

		// �������������� WebServer
		httplib::Server svr;

		// ������ ������
		if (svr.bind_to_port(server->config().web_get_ip().c_str(), server->config().web_get_port())) {

			std::cout << " - Web Server at port ";
			WriteColorText(handle, std::to_string(server->config().web_get_port()), 15);
			std::cout << std::endl << std::endl;
		
			// ������ ������� GET ��� ��� �������
			svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
				
				
				// �������� ������� ��������
				res.set_content("Welcome to PKO Web Server!", "text/plain");

			});
			
			// ������ ������� GET ��� ��� �������
			svr.Get("/stalls/", [&](const httplib::Request& req, httplib::Response& res) {

				// ��������, ��� ���� ����
				if (req.has_param("key")) {
					
					// ������� ����
					std::string key = req.get_param_value("key");

					// ��������, ��� ���� ������
					if (server->config().web_get_key().c_str() == key) {

						const PKO::player_list_t& players = server->getPlayers();

						// ������� ������ JSON
						json::JSON obj;
						
						auto i = players.begin();
						
						int j = 0;

						while (i != players.end())
						{
							PKO::CPlayer* ply = *i;

							// ��������, ��� ����� ����������
							if (ply->character().stall().installed()) {

								std::string j_str = std::to_string(j);
								int cell_count;

								obj["all_cha"][j_str] = json::Object();
								obj["all_cha"][j_str]["name"] = ply->character().getName();
								obj["all_cha"][j_str]["map_name"] = ply->character().getMap();
								obj["all_cha"][j_str]["pos_x"] = ply->character().getPosX();
								obj["all_cha"][j_str]["pos_y"] = ply->character().getPosY();
								obj["all_cha"][j_str]["stall_name"] = ply->character().stall().getName();
								obj["all_cha"][j_str]["stall_cell_count"] = cell_count = ply->character().stall().getCellCount();
								obj["all_cha"][j_str]["stall_type"] = ply->server()->connected() ? 1 : 0;

								if (cell_count) {

									int k = 0;

									for (int i = 0; i < 18; i++) {

										PKO::SStallCell cell = ply->character().stall().getCell(i);

										if (cell.count > 0) {

											// ���� ���-�� ������� - ������� ������ ��� ������
											if (cell_count == k)
												break;

											// �������� ����� ���������
											std::vector <PKO::SKitbagGrid> pKitbag = ply->character().kitbag();

											std::string k_str = std::to_string(k);

											obj["all_cha"][j_str]["stall_info"][k_str]["index"] = cell.grid;
											obj["all_cha"][j_str]["stall_info"][k_str]["id"] = pKitbag.at(cell.index).item_id;
											obj["all_cha"][j_str]["stall_info"][k_str]["count"] = cell.count;
											obj["all_cha"][j_str]["stall_info"][k_str]["amount"] = cell.money;

											k++;

										}

									}

								}

								j++;
							}

							i++;

						}

						
						// ������� �������� �� ���������.
						std::string ret = "There are currently no active stalls.";

						// ��������� ������� ��������
						if (j)
							ret = obj.dump();

						// ������� ���� � �������
						res.set_content(ret, "text/plain");

					}

				} else {

					// �������� ������� ��������
					res.set_content("Welcome to PKO Web Server!", "text/plain");
					
				}

			});

			// ������� ������
			svr.listen_after_bind();

		}

	}

	#endif

}

namespace PKO
{
	// �����������
	CProxyServer::CProxyServer(const CSettings& Config) :
		m_config(Config), m_player_pool(nullptr), m_thread_pool(nullptr), LastConnectTime(0)
	{
		// ������� ���� �������
		m_event_base = event_base_new();
		if (m_event_base == nullptr) {
			sendDebug("Couldn't create event base!");
			return;
		}
				
		// ������� ��� �������
		m_player_pool = new CObjectPool(new CPlayerMaker(this), m_config.player_pool_size());

		// ������� ��� �������
		m_thread_pool = new dbr::cc::ThreadPool(4);


	}

	// ����������
	CProxyServer::~CProxyServer()
	{

		// ������� ��� �������
		if (m_player_pool != nullptr) {
			delete m_player_pool;
		}

		// ������� ��� �������
		if (m_thread_pool != nullptr) {
			delete m_thread_pool;
		}

		// ������� ���� �������
		if (m_event_base != nullptr) {
			event_base_free(m_event_base);
		}

	}

	// �������� ���� �������
	event_base *CProxyServer::getBev() const
	{
		return m_event_base;
	}

	// �������� ����� ������������ ������� �� �������
	const CServerPacketHandlerManager& CProxyServer::getServerPacketHandlers() const
	{
		return m_server_packet_handlers;
	}

	// �������� ����� ������������ ������� �� �������
	const CClientPacketHandlerManager& CProxyServer::getClientPacketHandlers() const
	{
		return m_client_packet_handlers;
	}

	// �������� ������ �������
	const player_list_t& CProxyServer::getPlayers() const
	{
		return m_player_list;
	}

	// ���� ������ �� �����
	CPlayer* CProxyServer::FindPlayerByName(const std::string name) const
	{
		
		CPlayer* ret = NULL;

		for (size_t i = 0; i < m_player_list.size(); i++) {

			if (m_player_list[i]->character().getName() == name) {

				ret = m_player_list[i];
				break;

			}

		}

		return ret;

	}

	// ���� ������ �� Id
	CPlayer* CProxyServer::FindPlayerByID(const unsigned int id) const
	{

		CPlayer* ret = NULL;

		for (size_t i = 0; i < m_player_list.size(); i++) {

			if (m_player_list[i]->character().getId() == id) {

				ret = m_player_list[i];
				break;

			}

		}

		return ret;

	}


	// �������� ������ ���������
	const account_list_t& CProxyServer::getAccounts() const
	{
		return m_account_list;
	}

	// �������� ���������
	const CSettings& CProxyServer::config() const
	{
		return m_config;
	}

	// ��������� ������
	void CProxyServer::run()
	{

		#if ModuleAntiDBG
			// ������ ������ �� ��������� � ��� �������
			m_thread_pool->add(ProcessProtection::IsInjectedDBG);
		#endif

		// ���������, ��� � ��� ���� ���� �������
		if (m_event_base == nullptr) {
			throw stall_server_exception("Event base is null!");
		}
	
		// ������� � ��������� ��������� ���������� ������
		sockaddr_in localaddr;
		std::memset(reinterpret_cast<char *>(&localaddr), 0x00, sizeof(localaddr));
		localaddr.sin_family = AF_INET;
		localaddr.sin_addr.s_addr = ADDR_ANY;
		localaddr.sin_port = htons(m_config.listen_port());

		// ��������� ���������� �����
		evconnlistener *listener;
		listener = evconnlistener_new_bind( m_event_base, cb_accept, this,
											LEV_OPT_REUSEABLE, -1,
											reinterpret_cast<sockaddr*>(&localaddr), sizeof(localaddr) );
		if (listener == nullptr) {

			std::cout << "Couldn't start server on port ";
			WriteColorText(handle, std::to_string(m_config.listen_port()), 15);
			std::cout << "!" << std::endl;

			throw stall_server_exception("Error: port is busy!");
		}

		// ������� ������� �������
		timeval time;
		event *ev_timer = event_new(m_event_base, INVALID_SOCKET, EV_PERSIST, cb_timer, reinterpret_cast<void *>(this));
		// ������� �� ��������� �������
		time.tv_sec = 5; time.tv_usec = 0;
		evtimer_add(ev_timer, &time);

		std::cout << "[Servers Started]" << std::endl << std::endl;

		std::cout << " - Proxy Server at port ";
		WriteColorText(handle, std::to_string(m_config.listen_port()), 15);
		std::cout << std::endl;

		#if ModuleWeb

			// �������� ����� �� �������� ��� ������
			if (config().isWebEnable()) {

				// ������ Web Server � ��� �������
				m_thread_pool->add(Module::WebStart, this);

			}

		#endif

		// �������������� ����� �������
		event_base_dispatch(m_event_base);

		// ������� ���������
		evconnlistener_free(listener);
		// ������� ���������� �������
		event_free(ev_timer);

	}

	// ���������� � DEBUG
	void CProxyServer::sendDebug(std::string message)
	{
		auto current_time = std::chrono::system_clock::now();
		std::time_t rawTime = std::chrono::system_clock::to_time_t(current_time);
		struct tm timeinfo;
		localtime_s(&timeinfo, &rawTime);
		char buffer[32];
		std::strftime(buffer, 32, "%X", &timeinfo);
		std::stringstream log_text;
		log_text << "[" << buffer << "] ";
		log_text << message;
		std::cout << log_text.str() << std::endl;

	}

	void CProxyServer::UpdateTitle()
	{
		std::string title = "Connections: " + std::to_string(m_player_list.size()) + " Accounts: " + std::to_string(m_account_list.size());
		SetConsoleTitle(title.c_str());
	}

	// ������� ������ �����������
	void CProxyServer::account_connected(CPlayer* Player)
	{

		//std::cout << "Account Connected: " << Player << std::endl << std::endl;
		m_account_list.push_back(Player);
		Player->setCheckAutorization(false);
		UpdateTitle();

	}

	// ������� ��������� �����������
	void CProxyServer::account_disconnected(CPlayer* Player)
	{

		//std::cout << "Account Disconnected: " << Player << std::endl;
		auto std_find = std::find(m_account_list.begin(), m_account_list.end(), Player);
		if (std_find != m_account_list.end())
		{
			m_account_list.erase(std_find);
			Player->setCheckAutorization(true);
			UpdateTitle();
		}

	}

	// ������� �������� ����������
	void CProxyServer::player_connected(evutil_socket_t fd, sockaddr_in *address)
	{

		// ������� ������ ��� ������ ������
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_player_pool->acquire());

		//std::cout << "Player Connected: " << pPlayer << std::endl;

		// ����������� ���������� ����� ������
		pPlayer->server()->setIpAddress(CUtils::GetIpAddress(address));
		pPlayer->server()->setSocket(fd);

		// ������� ���� ���-�� ���������� � Proxy Server
		size_t maxConnecToStall = m_config.max_connect();

		// ���� ������� ������ ��� ��������� - ��������� ��� ����� ����������
		if (maxConnecToStall != NULL && (m_player_list.size() + 1) > maxConnecToStall) {

			// ��������� �������, ������ ��� ����� ������ �������!
			CDisconnectPacket disconnect_packet((CPlayer&)pPlayer, "Max Connect To Stall.");
			pPlayer->sendPacket(pPlayer->client(), &disconnect_packet);

		} else {

			// ���������� ���������
			//std::stringstream message;
			//message << "[connection] Client (0x" << pPlayer << ") " << pPlayer->server()->getIpAddress() << " joined the server!";
			//sendDebug(message.str());

			// �������������� ������
			pPlayer->protection().init(m_config.wpe_protection(), m_config.wpe_version());

			// ������������ � GateServer
			pPlayer->client()->setIpAddress(m_config.gate_server_ip());
			pPlayer->client()->setPort(m_config.gate_server_port());
			pPlayer->client()->open();

			// ������������� ����� �����
			pPlayer->setPingTime(GetTickCount64());

			// ������������� �������� �����������
			pPlayer->setCheckAutorization(true);

			// ��������� ������ � ������
			m_player_list.push_back(pPlayer);

			// ��������� ����� ���������� ����������
			UpdateLastConnectTime();

			// ��������� �����
			UpdateTitle();

		}

	}

	// ������� ���������� ������
	void CProxyServer::player_disconnected(CPlayer *pPlayer)
	{

		//std::cout << "Player Disconnected: " << pPlayer << std::endl;

		// ������� ������ �� ������
		auto std_find = std::find(m_player_list.begin(), m_player_list.end(), pPlayer);
		if (std_find != m_player_list.end())
		{
			try
			{
				m_player_list.erase(std_find);
				UpdateTitle();
			}
			catch (...)
			{
				std::cout << "Exception raised from player_disconnected{delete pPlayer from m_player_list}" << std::endl;
			}
		}
		else
		{
			std::cout << "player_disconnected erase failed" << std::endl;
		}

		// ������ ������ � ���
		m_player_pool->release(pPlayer);
	}

	// ������� �������
	void CProxyServer::on_timer()
	{

		//std::cout << "Player list count " << m_player_list.size() << std::endl;

		// ���� �� ���� ��������
		for (auto it = m_player_list.begin(); it != m_player_list.end(); ++it)
		{
			CPlayer* Player = (*it);
			if (Player)
			{
				CServerSocket* server = Player->server();
				if (server)
				{

					// ��������, ��� ������ ���������
					if (server->connected())
					{
						
						auto pingTime = GetTickCount64() - Player->getPingTime();

						// ������ ������� �����������
						if (Player->IsWaitAutorization())
						{

							// ������ ��������� ��� 1 �������
							if (pingTime > 1000)
							{

								// ��������� �������, ������ ��� ����� ������ �������!
								CDisconnectPacket disconnect_packet((CPlayer&)Player, "Autorization time.");
								Player->sendPacket(Player->client(), &disconnect_packet);
								
							}

						} else {
							
							if (pingTime > 10000) {

								// ��������� �������, ������ ��� ����� ������ �������!
								CDisconnectPacket disconnect_packet((CPlayer&)Player, "Ping.");
								Player->sendPacket(Player->client(), &disconnect_packet);
								
							}

						}

					} else {

						if (Player->character().stall().installed() == true)
						{

							// ������ ������� � ������
							// �������� ��������� ������������� ������� ��������
							unsigned int max_time = m_config.max_offline_trade_time();
							if (max_time > 0)
							{
								if (GetTickCount64() - Player->character().stall().getInstallTick() > max_time)
								{
									// ����� ����� �������
									// ��������� ���
									CDisconnectPacket disconnect_packet((CPlayer&)Player, "Max offline stall time.");
									Player->sendPacket(server, &disconnect_packet);
								}
							}

						} else {

							CDisconnectPacket disconnect_packet((CPlayer&)Player, "Close connecting.");
							Player->sendPacket(Player->client(), &disconnect_packet);
							
						}
					}
				}
				else
				{
					std::cout << "Server == nullptr" << std::endl;
				}
			}
			else
			{
				std::cout << "Player == nullptr" << std::endl;
			}
		}

	}
}