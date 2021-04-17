#include "callback.h"
#include "../Class/ProxyServer/ProxyServer.h"
#include "ISocket.h"
#include "../Class/Player/Player.h"

namespace PKO
{
	// Событие подключения клиента
	void cb_accept(evconnlistener *listener, evutil_socket_t fd, sockaddr *address, int socklen, void *ctx)
	{
		// Получим указатель на объект сервера
		CProxyServer *pServer = reinterpret_cast<CProxyServer *>(ctx);
		if (pServer != nullptr && fd != INVALID_SOCKET) {

			// Ограничиваем подключения в пол секунды
			if (pServer->GetLastConnectTime() > pServer->config().connect_interval()) {

				// Вызываем событие подключения
				pServer->player_connected(fd, reinterpret_cast<sockaddr_in*>(address));

			} else {

				// Если не прошло пол-секунды - отключаем сокет
				evutil_closesocket(fd);

			}

		}

	}

	// Событие чтения данных из сокета
	void cb_read(bufferevent *fd, void *arg)
	{
		// Получим указатель на сокет
		ISocket *pSocket = reinterpret_cast<ISocket *>(arg);
		if (pSocket != nullptr) {
			pSocket->on_data_recevied();
		}
	}

	// Событие на сокете
	void cb_event(bufferevent *fd, short int what, void *arg)
	{
		// Получим указатель на сокет
		ISocket *pSocket = reinterpret_cast<ISocket *>(arg);
		if (pSocket == nullptr) {
			return;
		}

		// Проверяем код события
		if (what & BEV_EVENT_CONNECTED) {
			// Клиент подключился
			pSocket->on_connected();
			return;
		}

		if (what & BEV_EVENT_EOF) {
			// Клиент отключился
			pSocket->on_disconnected();
			return;
		}

		if (what & BEV_EVENT_ERROR) {
			// Ошибка на сокете клиента
			pSocket->on_error(EVUTIL_SOCKET_ERROR());
			return;
		}
	}

	// Событие переподключения
	void cb_login(evutil_socket_t fd, short int what, void *arg)
	{
		CPlayer *pPlayer = reinterpret_cast<CPlayer *>(arg);
		if (pPlayer != nullptr) {
			pPlayer->relogin();
		}
	}

	// Событие таймера
	void cb_timer(evutil_socket_t fd, short int what, void *arg)
	{

		CProxyServer *pServer = reinterpret_cast<CProxyServer *>(arg);
		if (pServer != nullptr) {
			pServer->on_timer();
		}
	}

}