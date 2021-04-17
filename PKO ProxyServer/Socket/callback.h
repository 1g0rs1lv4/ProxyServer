#pragma once

#include <event2\listener.h>
#include <event2\bufferevent.h>

namespace PKO
{
	// ������� ����������� �������
	void cb_accept(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *address, int socklen, void *ctx);

	// ������� ������ ������ �� ������
	void cb_read(bufferevent *fd, void *arg);

	// ������� �� ������
	void cb_event(bufferevent *fd, short int what, void *arg);

	// ������� ���������������
	void cb_login(evutil_socket_t fd, short int what, void *arg);

	// ������� �������
	void cb_timer(evutil_socket_t fd, short int what, void *arg);

}