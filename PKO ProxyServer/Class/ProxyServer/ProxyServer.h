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

	// ��� ��� ������ �������
	typedef std::vector<CPlayer *> player_list_t;
	typedef std::vector<CPlayer* > account_list_t;
	
	// ��������� ����� ���������� ��� �������
	class stall_server_exception : public std::runtime_error
	{
		public:
			stall_server_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~stall_server_exception() { }
	};

	// ����� ������� ������� �������
	class CProxyServer
	{
		public:

			// �����������
			CProxyServer(const CSettings& Config);

			// ����������
			~CProxyServer();

			// ��������� �������
			void run();

			// �������� ���� �������
			event_base *getBev() const;

			// �������� ����������� �������
			const CServerPacketHandlerManager& getServerPacketHandlers() const;
			const CClientPacketHandlerManager& getClientPacketHandlers() const;

			// ���������� � DEBUG
			void sendDebug(std::string message);

			// �������� ������ �������
			const player_list_t& getPlayers() const;

			// ���� ������ �� �����
			CPlayer* FindPlayerByName(const std::string name) const;

			// ���� ������ �� Id
			CPlayer* FindPlayerByID(const unsigned int id) const;

			// ���������� ����� ���������� �����������
			DWORD GetLastConnectTime() { return GetTickCount() - LastConnectTime; }

			// ������������� ����� ���������� �����������
			DWORD UpdateLastConnectTime() { return LastConnectTime = GetTickCount(); }

			// �������� ������ ���������
			const account_list_t& getAccounts() const;

			// �������� ���������
			const CSettings& config() const;

		private:

			// ������������� ������� � ������
			friend class CPlayer;
			friend void cb_accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);
			friend void cb_timer(evutil_socket_t fd, short int what, void *arg);

			// �������� �����������
			CProxyServer(const CProxyServer&) = delete;
			CProxyServer& operator=(const CProxyServer&) = delete;

			// ������� ������ �����������
			void CProxyServer::account_connected(CPlayer* Player);

			// ������� ��������� �����������
			void CProxyServer::account_disconnected(CPlayer* Player);

			// ������� ����������� �������
			void player_connected(evutil_socket_t fd, sockaddr_in *address);

			// ������� ���������� ������
			void player_disconnected(CPlayer *pPlayer);

			// ������� �������
			void on_timer();

			// �������� ��������� ����
			void UpdateTitle();

			// ���� �������
			event_base *m_event_base;

			// ��� �������
			CObjectPool *m_player_pool;

			// ��� �������
			dbr::cc::ThreadPool* m_thread_pool;

			// ����������� �������
			CServerPacketHandlerManager m_server_packet_handlers;
			CClientPacketHandlerManager m_client_packet_handlers;

			// ������ �������
			player_list_t m_player_list;

			// ������ ���������
			account_list_t m_account_list;

			// ���������
			const CSettings& m_config;

			// ����� ���������� �����������
			DWORD LastConnectTime;

	};
}



