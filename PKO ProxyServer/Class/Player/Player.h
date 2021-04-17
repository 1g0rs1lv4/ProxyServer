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

	// Класс игрока
	class CPlayer : public IPoolable, 
		public INetClientObserver, public INetServerObserver
	{
		public:

			// Конструктор
			CPlayer(CProxyServer *pServer);

			// Деструктор
			~CPlayer();

			// Сбросить состояние
			void reset();

			// Получить указатель на сервер ларьков
			CProxyServer *stall_server() const;

			// Получить сокет сервера
			CServerSocket *server() const;

			// Получить сокет клиента
			CClientSocket *client() const;

			// Получить аккаунт
			CAccount& account();

			// Получить персонажа
			CCharacter& character();

			// Получить объект для шифрования пакетов
			CPacketEncryptor& packet_encryptor();

			// Получить объект защиты
			CProtection& protection();

			// DEBUG сообщение от клиента
			void sendDebug(std::string message);

			// Отправить пакет
			void sendPacket(CBaseSocket *pSocket, IPacket *pPacket);

			// Перезайти на аккаунт
			void do_relogin();

			// Получить время пинга
			unsigned __int64 getPingTime() const;

			// Установить время пинга
			void setPingTime(unsigned __int64 time);

			// Получить время подключения
			unsigned __int64 getLoginTime() const;

			// Устанавливаем время подключения
			void setLoginTime(unsigned __int64 time);

			// Получить авторизировано ли соединение
			bool IsWaitAutorization() const;

			// Устанавливаем авторизировано ли соединение
			void setCheckAutorization(bool val);

			// Авторизация на сервере
			void on_server_login();

			// Прекращение авторизации на сервере
			void on_server_logout();

		private:
			
			// Дружественные функции
			friend void cb_login(evutil_socket_t fd, short int what, void* arg);
			
			// Запретим копирование
			CPlayer(const CPlayer&) = delete;
			CPlayer& operator=(const CPlayer&) = delete;

			// Наблюдатель за серверным сокетом
			virtual void on_client_disconnected();
			virtual void on_client_recived_data(const char *data, size_t length);
			virtual void on_client_error(int errcode);

			// Наблюдатель за клиентским сокетом
			virtual void on_server_connected();
			virtual void on_server_disconnected();
			virtual void on_server_recived_data(const char *data, size_t length);
			virtual void on_server_error(int errcode);

			// Перезайти на аккаунт
			void relogin();

			// Указатель на сервер
			CProxyServer *m_server;

			// Сокеты сервера
			CServerSocket *m_server_socket;
			CClientSocket *m_client_socket;

			// Объекты для бинарного чтения и записи
			CBinaryReader m_reader;
			CBinaryWriter m_writer;

			// Аккаунт и персонаж
			CAccount m_account;
			CCharacter m_character;

			// Событие переполключения
			event *m_relogin_event;

			// Шифрование пакетов
			CPacketEncryptor m_packet_encryptor;

			// Защита сервера
			CProtection m_protection;

			// Время пинга
			unsigned __int64 m_ping_time;

			// Время подключения
			unsigned __int64 m_login_time;

			// Авторизовался ли аккаунт
			bool isAutorization;
			
			// Первый ли пакет
			bool IsFirstPacket;

	};

}
