#pragma once

#include <event2\listener.h>
#include <event2\bufferevent.h>

namespace PKO
{
	// Событие подключения клиента
	void cb_accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);

	// Событие чтения данных из сокета
	void cb_read(bufferevent *fd, void *arg);

	// Событие на сокете
	void cb_event(bufferevent *fd, short int what, void *arg);

	// Событие переподключения
	void cb_login(evutil_socket_t fd, short int what, void *arg);

	// Событие таймера
	void cb_timer(evutil_socket_t fd, short int what, void *arg);

}