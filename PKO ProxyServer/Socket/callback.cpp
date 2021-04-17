#include "callback.h"
#include "../Class/ProxyServer/ProxyServer.h"
#include "ISocket.h"
#include "../Class/Player/Player.h"

namespace PKO
{
	// ������� ����������� �������
	void cb_accept(evconnlistener *listener, evutil_socket_t fd, sockaddr *address, int socklen, void *ctx)
	{
		// ������� ��������� �� ������ �������
		CProxyServer *pServer = reinterpret_cast<CProxyServer *>(ctx);
		if (pServer != nullptr && fd != INVALID_SOCKET) {

			// ������������ ����������� � ��� �������
			if (pServer->GetLastConnectTime() > pServer->config().connect_interval()) {

				// �������� ������� �����������
				pServer->player_connected(fd, reinterpret_cast<sockaddr_in*>(address));

			} else {

				// ���� �� ������ ���-������� - ��������� �����
				evutil_closesocket(fd);

			}

		}

	}

	// ������� ������ ������ �� ������
	void cb_read(bufferevent *fd, void *arg)
	{
		// ������� ��������� �� �����
		ISocket *pSocket = reinterpret_cast<ISocket *>(arg);
		if (pSocket != nullptr) {
			pSocket->on_data_recevied();
		}
	}

	// ������� �� ������
	void cb_event(bufferevent *fd, short int what, void *arg)
	{
		// ������� ��������� �� �����
		ISocket *pSocket = reinterpret_cast<ISocket *>(arg);
		if (pSocket == nullptr) {
			return;
		}

		// ��������� ��� �������
		if (what & BEV_EVENT_CONNECTED) {
			// ������ �����������
			pSocket->on_connected();
			return;
		}

		if (what & BEV_EVENT_EOF) {
			// ������ ����������
			pSocket->on_disconnected();
			return;
		}

		if (what & BEV_EVENT_ERROR) {
			// ������ �� ������ �������
			pSocket->on_error(EVUTIL_SOCKET_ERROR());
			return;
		}
	}

	// ������� ���������������
	void cb_login(evutil_socket_t fd, short int what, void *arg)
	{
		CPlayer *pPlayer = reinterpret_cast<CPlayer *>(arg);
		if (pPlayer != nullptr) {
			pPlayer->relogin();
		}
	}

	// ������� �������
	void cb_timer(evutil_socket_t fd, short int what, void *arg)
	{

		CProxyServer *pServer = reinterpret_cast<CProxyServer *>(arg);
		if (pServer != nullptr) {
			pServer->on_timer();
		}
	}

}