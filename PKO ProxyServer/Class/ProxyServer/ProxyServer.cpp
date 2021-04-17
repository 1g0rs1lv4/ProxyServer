//#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <iostream>
#include <event2\listener.h>
#include "ProxyServer.h"
#include "../Utils/Utils.h"
#include "../../Socket/callback.h"
#include "../../Pool/PlayerMaker.h"
#include "../../Class/Player/Player.h"
#include "../../Client/Packet/DisconnectPacket.h"

// Инициализируем веб сервер
#include "../../Class/WebServer/httplib.h"
#include "../../Class/WebServer/json.hpp"

// Подключаем защиту от отладчика
#include "../../Protect/Protect.h"

// Обработчик консоли
extern HANDLE handle;

// Напечатать цветом
extern void WriteColorText(HANDLE handle, std::string str, WORD color);

namespace Module {

	#if ModuleWeb

		// Запускаем WebServer
	void WebStart(PKO::CProxyServer* server) {

		// Инициализируем WebServer
		httplib::Server svr;

		// Биндим соккет
		if (svr.bind_to_port(server->config().web_get_ip().c_str(), server->config().web_get_port())) {

			std::cout << " - Web Server at port ";
			WriteColorText(handle, std::to_string(server->config().web_get_port()), 15);
			std::cout << std::endl << std::endl;
		
			// Задаем правила GET для веб сервера
			svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
				
				
				// Присвоим контент страницы
				res.set_content("Welcome to PKO Web Server!", "text/plain");

			});
			
			// Задаем правила GET для веб сервера
			svr.Get("/stalls/", [&](const httplib::Request& req, httplib::Response& res) {

				// Убедимся, что есть ключ
				if (req.has_param("key")) {
					
					// Считаем ключ
					std::string key = req.get_param_value("key");

					// Убедимся, что ключ верный
					if (server->config().web_get_key().c_str() == key) {

						const PKO::player_list_t& players = server->getPlayers();

						// Создаем обьект JSON
						json::JSON obj;
						
						auto i = players.begin();
						
						int j = 0;

						while (i != players.end())
						{
							PKO::CPlayer* ply = *i;

							// Убедимся, что ларек установлен
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

											// Если кол-во совпало - считать дальше нет смысла
											if (cell_count == k)
												break;

											// Получаем ранец персонажа
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

						
						// Контент страницы по умолчанию.
						std::string ret = "There are currently no active stalls.";

						// Формируем контент страницы
						if (j)
							ret = obj.dump();

						// Выводим инфо о ларьках
						res.set_content(ret, "text/plain");

					}

				} else {

					// Присвоим контент страницы
					res.set_content("Welcome to PKO Web Server!", "text/plain");
					
				}

			});

			// Слушаем соккет
			svr.listen_after_bind();

		}

	}

	#endif

}

namespace PKO
{
	// Конструктор
	CProxyServer::CProxyServer(const CSettings& Config) :
		m_config(Config), m_player_pool(nullptr), m_thread_pool(nullptr), LastConnectTime(0)
	{
		// Создаем ядро событий
		m_event_base = event_base_new();
		if (m_event_base == nullptr) {
			sendDebug("Couldn't create event base!");
			return;
		}
				
		// Создаем пул игроков
		m_player_pool = new CObjectPool(new CPlayerMaker(this), m_config.player_pool_size());

		// Создаем пул потоков
		m_thread_pool = new dbr::cc::ThreadPool(4);


	}

	// Деструктор
	CProxyServer::~CProxyServer()
	{

		// Удаляем пул игроков
		if (m_player_pool != nullptr) {
			delete m_player_pool;
		}

		// Удаляем пул потоков
		if (m_thread_pool != nullptr) {
			delete m_thread_pool;
		}

		// Удаляем ядро событий
		if (m_event_base != nullptr) {
			event_base_free(m_event_base);
		}

	}

	// Получить ядро событий
	event_base *CProxyServer::getBev() const
	{
		return m_event_base;
	}

	// Получить набор обработчиков пакетов от сервера
	const CServerPacketHandlerManager& CProxyServer::getServerPacketHandlers() const
	{
		return m_server_packet_handlers;
	}

	// Получить набор обработчиков пакетов от клиента
	const CClientPacketHandlerManager& CProxyServer::getClientPacketHandlers() const
	{
		return m_client_packet_handlers;
	}

	// Получить список игроков
	const player_list_t& CProxyServer::getPlayers() const
	{
		return m_player_list;
	}

	// Ищем игрока по имени
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

	// Ищем игрока по Id
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


	// Получить список аккаунтов
	const account_list_t& CProxyServer::getAccounts() const
	{
		return m_account_list;
	}

	// Получить настройки
	const CSettings& CProxyServer::config() const
	{
		return m_config;
	}

	// Запустить сервер
	void CProxyServer::run()
	{

		#if ModuleAntiDBG
			// Отдаем Защиту от Отладчика в пул потоков
			m_thread_pool->add(ProcessProtection::IsInjectedDBG);
		#endif

		// Проверяем, что у нас есть ядро событий
		if (m_event_base == nullptr) {
			throw stall_server_exception("Event base is null!");
		}
	
		// Создаем и заполняем структуру локального адреса
		sockaddr_in localaddr;
		std::memset(reinterpret_cast<char *>(&localaddr), 0x00, sizeof(localaddr));
		localaddr.sin_family = AF_INET;
		localaddr.sin_addr.s_addr = ADDR_ANY;
		localaddr.sin_port = htons(m_config.listen_port());

		// Слушатель локального порта
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

		// Создаем событие таймера
		timeval time;
		event *ev_timer = event_new(m_event_base, INVALID_SOCKET, EV_PERSIST, cb_timer, reinterpret_cast<void *>(this));
		// секунда на отработку функций
		time.tv_sec = 5; time.tv_usec = 0;
		evtimer_add(ev_timer, &time);

		std::cout << "[Servers Started]" << std::endl << std::endl;

		std::cout << " - Proxy Server at port ";
		WriteColorText(handle, std::to_string(m_config.listen_port()), 15);
		std::cout << std::endl;

		#if ModuleWeb

			// Проверим нужно ли включать веб сервер
			if (config().isWebEnable()) {

				// Отдаем Web Server в пул потоков
				m_thread_pool->add(Module::WebStart, this);

			}

		#endif

		// Инициализируем поток эвентов
		event_base_dispatch(m_event_base);

		// Удаляем слушателя
		evconnlistener_free(listener);
		// Удаляем обработчик времени
		event_free(ev_timer);

	}

	// Напечатать в DEBUG
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

	// Аккаунт прошёл авторизацию
	void CProxyServer::account_connected(CPlayer* Player)
	{

		//std::cout << "Account Connected: " << Player << std::endl << std::endl;
		m_account_list.push_back(Player);
		Player->setCheckAutorization(false);
		UpdateTitle();

	}

	// Аккаунт прекратил авторизацию
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

	// Принять входящее соединение
	void CProxyServer::player_connected(evutil_socket_t fd, sockaddr_in *address)
	{

		// Получае обьект для записи игрока
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_player_pool->acquire());

		//std::cout << "Player Connected: " << pPlayer << std::endl;

		// Настраиваем клиентский сокет игрока
		pPlayer->server()->setIpAddress(CUtils::GetIpAddress(address));
		pPlayer->server()->setSocket(fd);

		// Считаем макс кол-во соединений к Proxy Server
		size_t maxConnecToStall = m_config.max_connect();

		// Если игроков больше чем разрешено - отсеиваем все новые соединения
		if (maxConnecToStall != NULL && (m_player_list.size() + 1) > maxConnecToStall) {

			// Отключаем клиента, потому что время ответа истекло!
			CDisconnectPacket disconnect_packet((CPlayer&)pPlayer, "Max Connect To Stall.");
			pPlayer->sendPacket(pPlayer->client(), &disconnect_packet);

		} else {

			// Отладочное сообщение
			//std::stringstream message;
			//message << "[connection] Client (0x" << pPlayer << ") " << pPlayer->server()->getIpAddress() << " joined the server!";
			//sendDebug(message.str());

			// Инициализируем защиту
			pPlayer->protection().init(m_config.wpe_protection(), m_config.wpe_version());

			// Подключаемся к GateServer
			pPlayer->client()->setIpAddress(m_config.gate_server_ip());
			pPlayer->client()->setPort(m_config.gate_server_port());
			pPlayer->client()->open();

			// Устанавливаем время пинга
			pPlayer->setPingTime(GetTickCount64());

			// Устанавливаем проверку авторизации
			pPlayer->setCheckAutorization(true);

			// Добавляем игрока в список
			m_player_list.push_back(pPlayer);

			// Обновляем время последнего соединения
			UpdateLastConnectTime();

			// Обновляем шапку
			UpdateTitle();

		}

	}

	// Событие отключения игрока
	void CProxyServer::player_disconnected(CPlayer *pPlayer)
	{

		//std::cout << "Player Disconnected: " << pPlayer << std::endl;

		// Удаляем игрока из списка
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

		// Отдаем игрока в пул
		m_player_pool->release(pPlayer);
	}

	// Событие таймера
	void CProxyServer::on_timer()
	{

		//std::cout << "Player list count " << m_player_list.size() << std::endl;

		// Цикл по всем клиентам
		for (auto it = m_player_list.begin(); it != m_player_list.end(); ++it)
		{
			CPlayer* Player = (*it);
			if (Player)
			{
				CServerSocket* server = Player->server();
				if (server)
				{

					// Проверим, что клиент подключен
					if (server->connected())
					{
						
						auto pingTime = GetTickCount64() - Player->getPingTime();

						// Клиент ожидает авторизацию
						if (Player->IsWaitAutorization())
						{

							// Клиент подключён уже 1 секунду
							if (pingTime > 1000)
							{

								// Отключаем клиента, потому что время ответа истекло!
								CDisconnectPacket disconnect_packet((CPlayer&)Player, "Autorization time.");
								Player->sendPacket(Player->client(), &disconnect_packet);
								
							}

						} else {
							
							if (pingTime > 10000) {

								// Отключаем клиента, потому что время ответа истекло!
								CDisconnectPacket disconnect_packet((CPlayer&)Player, "Ping.");
								Player->sendPacket(Player->client(), &disconnect_packet);
								
							}

						}

					} else {

						if (Player->character().stall().installed() == true)
						{

							// Клиент торгует в ларьке
							// Проверим настройки максимального времени торговли
							unsigned int max_time = m_config.max_offline_trade_time();
							if (max_time > 0)
							{
								if (GetTickCount64() - Player->character().stall().getInstallTick() > max_time)
								{
									// Игрок долго торгует
									// Отключаем его
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