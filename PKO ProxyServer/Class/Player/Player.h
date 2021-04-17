#pragma once
#include <event2\event.h>
#include "../../Pool/IPoolable.h"
#include "../../Socket/INetObserver.h"
#include "../../Main/IPacket.h"
#include "../../Class/ProxyServer/ProxyServer.h"
#include "../../Socket/ServerSocket.h"
#include "../../Socket/ClientSocket.h"
#include "../../Binary/BinaryReader.h"
#include "../../Binary/BinaryWriter.h"
#include "../../Class/Account/Account.h"
#include "../../Class/Character/Character.h"
#include "../../Class/PacketEncryptor/PacketEncryptor.h"
#include "../../Class/Protection/Protection.h"

namespace PKO
{

	// ����� ������
	class CPlayer : public IPoolable, 
		public INetClientObserver, public INetServerObserver
	{
		public:

			// �����������
			CPlayer(CProxyServer *pServer);

			// ����������
			~CPlayer();

			// �������� ���������
			void reset();

			// �������� ��������� �� ������ �������
			CProxyServer *stall_server() const;

			// �������� ����� �������
			CServerSocket *server() const;

			// �������� ����� �������
			CClientSocket *client() const;

			// �������� �������
			CAccount& account();

			// �������� ���������
			CCharacter& character();

			// �������� ������ ��� ���������� �������
			CPacketEncryptor& packet_encryptor();

			// �������� ������ ������
			CProtection& protection();

			// DEBUG ��������� �� �������
			void sendDebug(std::string message);

			// ��������� �����
			void sendPacket(CBaseSocket *pSocket, IPacket *pPacket);

			// ��������� �� �������
			void do_relogin();

			// �������� ����� �����
			unsigned __int64 getPingTime() const;

			// ���������� ����� �����
			void setPingTime(unsigned __int64 time);

			// �������� ����� �����������
			unsigned __int64 getLoginTime() const;

			// ������������� ����� �����������
			void setLoginTime(unsigned __int64 time);

			// �������� �������������� �� ����������
			bool IsWaitAutorization() const;

			// ������������� �������������� �� ����������
			void setCheckAutorization(bool val);

			// ����������� �� �������
			void on_server_login();

			// ����������� ����������� �� �������
			void on_server_logout();

		private:
			
			// ������������� �������
			friend void cb_login(evutil_socket_t fd, short int what, void* arg);
			
			// �������� �����������
			CPlayer(const CPlayer&) = delete;
			CPlayer& operator=(const CPlayer&) = delete;

			// ����������� �� ��������� �������
			virtual void on_client_disconnected();
			virtual void on_client_recived_data(const char *data, size_t length);
			virtual void on_client_error(int errcode);

			// ����������� �� ���������� �������
			virtual void on_server_connected();
			virtual void on_server_disconnected();
			virtual void on_server_recived_data(const char *data, size_t length);
			virtual void on_server_error(int errcode);

			// ��������� �� �������
			void relogin();

			// ��������� �� ������
			CProxyServer *m_server;

			// ������ �������
			CServerSocket *m_server_socket;
			CClientSocket *m_client_socket;

			// ������� ��� ��������� ������ � ������
			CBinaryReader m_reader;
			CBinaryWriter m_writer;

			// ������� � ��������
			CAccount m_account;
			CCharacter m_character;

			// ������� ���������������
			event *m_relogin_event;

			// ���������� �������
			CPacketEncryptor m_packet_encryptor;

			// ������ �������
			CProtection m_protection;

			// ����� �����
			unsigned __int64 m_ping_time;

			// ����� �����������
			unsigned __int64 m_login_time;

			// ������������� �� �������
			bool isAutorization;
			
			// ������ �� �����
			bool IsFirstPacket;

	};

}
