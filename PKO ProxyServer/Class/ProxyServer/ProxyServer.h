#pragma once
#include <string>
#include <exception>
#include <vector>
#include <event2\event.h>
#include <map>
#include "../../Class/Settings/Settings.h"
#include "../../Pool/ObjectPool.h"
#include "../../Thread/ThreadPool.hpp"
#include "../../Server/ServerPacketHandlerManager.h"
#include "../../Client/ClientPacketHandlerManager.h"


namespace PKO
{
	
	class CPlayer;

	// Тип для списка игроков
	typedef std::vector<CPlayer *> player_list_t;
	typedef std::vector<CPlayer* > account_list_t;
	
	// Определим класс исключения для сервера
	class stall_server_exception : public std::runtime_error
	{
		public:
			stall_server_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~stall_server_exception() { }
	};

	// Класс сервера оффлайн ларьков
	class CProxyServer
	{
		public:

			// Конструктор
			CProxyServer(const CSettings& Config);

			// Деструктор
			~CProxyServer();

			// Запустить сервера
			void run();

			// Получить ядро событий
			event_base *getBev() const;

			// Получить обработчики пакетов
			const CServerPacketHandlerManager& getServerPacketHandlers() const;
			const CClientPacketHandlerManager& getClientPacketHandlers() const;

			// Напечатать в DEBUG
			void sendDebug(std::string message);

			// Получить список игроков
			const player_list_t& getPlayers() const;

			// Ищем игрока по имени
			CPlayer* FindPlayerByName(const std::string name) const;

			// Ищем игрока по Id
			CPlayer* FindPlayerByID(const unsigned int id) const;

			// Возвращает время последнего подключения
			DWORD GetLastConnectTime() { return GetTickCount() - LastConnectTime; }

			// Устанавливает время последнего подключения
			DWORD UpdateLastConnectTime() { return LastConnectTime = GetTickCount(); }

			// Получить список аккаунтов
			const account_list_t& getAccounts() const;

			// Получить настройки
			const CSettings& config() const;

		private:

			// Дружественные функции и классы
			friend class CPlayer;
			friend void cb_accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
			friend void cb_timer(evutil_socket_t fd, short int what, void *arg);

			// Запретим копирование
			CProxyServer(const CProxyServer&) = delete;
			CProxyServer& operator=(const CProxyServer&) = delete;

			// Аккаунт прошёл авторизацию
			void CProxyServer::account_connected(CPlayer* Player);

			// Аккаунт прекратил авторизацию
			void CProxyServer::account_disconnected(CPlayer* Player);

			// Событие подключения клиента
			void player_connected(evutil_socket_t fd, sockaddr_in *address);

			// Событие отключения игрока
			void player_disconnected(CPlayer *pPlayer);

			// Событие таймера
			void on_timer();

			// Обновить заголовок окна
			void UpdateTitle();

			// Ядро событий
			event_base *m_event_base;

			// Пул игроков
			CObjectPool *m_player_pool;

			// Пул потоков
			dbr::cc::ThreadPool* m_thread_pool;

			// Обработчики пакетов
			CServerPacketHandlerManager m_server_packet_handlers;
			CClientPacketHandlerManager m_client_packet_handlers;

			// Список игроков
			player_list_t m_player_list;

			// Список аккаунтов
			account_list_t m_account_list;

			// Настройки
			const CSettings& m_config;

			// Время последнего подключения
			DWORD LastConnectTime;

	};
}



