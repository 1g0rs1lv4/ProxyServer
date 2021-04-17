#include <event2\event.h>
#include <iostream>
#include "Player.h"
#include "../../Socket/callback.h"
#include "../../Socket/INetSubject.h"
#include "../../Binary/BinaryReader.h"
#include "../../Client/Packet/LoginPacket.h"
#include "../../Server/Packet/WrongVersionPacket.h"
#include "../../Client/Packet/DisconnectPacket.h"
#include <sstream>
#include <chrono>
#include <ctime>

namespace PKO
{
	// Конструктор
	CPlayer::CPlayer(CProxyServer *pServer) :
		m_server(pServer), m_ping_time(0), m_login_time(0), isAutorization(false), IsFirstPacket(true)
	{

		// Создаем сокет сервера 
		m_server_socket = new CServerSocket(pServer->getBev(), 16368, 16368);
		m_server_socket->setSubject(new CNetServerSubject(this));

		// Создаем сокет клиента
		m_client_socket = new CClientSocket(pServer->getBev(), 16368, 16368);
		m_client_socket->setSubject(new CNetClientSubject(this));
		
		// Событие переподключения
		m_relogin_event = evtimer_new(pServer->getBev(), cb_login, this);
	}

	// Деструктор
	CPlayer::~CPlayer()
	{
		evtimer_del(m_relogin_event);
		delete m_server_socket;
		delete m_client_socket;
	}

	// Сбросить состояние
	void CPlayer::reset()
	{

		// Сбросим сокеты
		m_server_socket->reset();
		m_client_socket->reset();

		// Сбросим аккаунт
		m_account.setLogin("");
		m_account.setPassword("");
		m_account.setMacAddress("");
		m_account.setChapString("");
		m_account.setBillString("");
		m_account.setFlag(0);
		m_account.setVersion(0);
		m_account.setEncryptionKey(nullptr, 0);

		// Сбросим персонажа
		m_character.setId(0);
		m_character.setName("");
		m_character.setMap("");
		m_character.setPos(0, 0);

		// Сбросим ларек персонажа
		m_character.stall().init();

		// Сбросим инвентарь персонажа
		m_character.setKitbagSize(0);
		m_character.kitbag().clear();

		// Шифрование пакетов
		m_packet_encryptor.init(false, m_account);
		m_ping_time = 0;
		m_login_time = 0;
		isAutorization = false;

	}

	// Получить сокет сервера
	CServerSocket *CPlayer::server() const
	{
		return m_server_socket;
	}

	// Получить сокет клиента
	CClientSocket *CPlayer::client() const
	{
		return m_client_socket;
	}

	// Получить указатель на сервер ларьков
	CProxyServer *CPlayer::stall_server() const
	{
		return m_server;
	}

	// Получить аккаунт
	CAccount& CPlayer::account()
	{
		return m_account;
	}

	// Получить персонажа
	CCharacter& CPlayer::character()
	{
		return m_character;
	}

	// Получить объект для шифрования пакетов
	CPacketEncryptor& CPlayer::packet_encryptor()
	{
		return m_packet_encryptor;
	}

	// Получить объект защиты
	CProtection& CPlayer::protection()
	{
		return m_protection;
	}

	// Отправить пакет
	void CPlayer::sendPacket(CBaseSocket *pSocket, 
										IPacket *pPacket)
	{
		try
		{
			// Получим буфер
			CNetBuffer *pBuf = pSocket->send_buf();

			// Устанавливаем буфер для записи
			m_writer.setData(const_cast<char *>(pBuf->data()), pBuf->size());
			m_writer.seek(0, seek_type_t::seek_begin);

			// Пишем заголовок пакета
			m_writer.writeUint16(0);
			m_writer.writeUint32(0x80000000);
			m_writer.writeUint16(pPacket->getId());

			// Пишем тело пакета
			pPacket->write(m_writer);

			// Пишем размер пакета
			unsigned short int block_size = static_cast<unsigned short int>(m_writer.tell());
			m_writer.seek(0, seek_type_t::seek_begin);
			m_writer.writeUint16(block_size);

			// Шифруем пакет
			if (m_packet_encryptor.enabled())
			{
				if (block_size >= 6)
				{
					//printf(" * block_size = %i\n", block_size);
					if (pSocket->is_server()) {
						try {
							m_packet_encryptor.encrypt((m_writer.data() + 6), (block_size - 6), encrypt_t::enc_sc);
						}
						catch (...) {
							printf("* [0] catch encrypt\n");
						}
					}
					else {
						try {
							m_packet_encryptor.encrypt((m_writer.data() + 6), (block_size - 6), encrypt_t::enc_cs);
						}
						catch (...) {
							printf("* [1] catch encrypt\n");
						}
					}
				}
				else
				{
					//printf("******************* block_size = %i\n", block_size);
				}
			}

			// Отправляем пакет
			pSocket->write(m_writer.data(), block_size);

			// Очищаем буфер
			pBuf->set_length(block_size);
			pBuf->clear();
		}
		catch (const binary_io_exception&) {
		//	std::cout << e.what() << std::endl;
		}
		catch (const std::runtime_error&) {
		//	std::cout << e.what() << std::endl;
		}
		catch (...) {
		//	std::cout << "Unknown error while sending packet!" << std::endl;
		}
	}

	void CPlayer::sendDebug(std::string msg)
	{
		std::stringstream message;
		message << "[0x" << this << "][" << account().getLogin() << "] " << msg;
		m_server->sendDebug(message.str());
	}

	// ===============================================
	// Наблюдатель за серверным сокетом
	// ===============================================

	// Клиент отключился
	void CPlayer::on_client_disconnected()
	{

		// Обнуляем первый пакет
		IsFirstPacket = true;

		if (!m_character.stall().installed() || m_character.stall().empty()) {

			m_client_socket->close();

		}

	}

	// От клиента получены данные
	void CPlayer::on_client_recived_data(const char *data, size_t length)
	{	

		try
		{
			// Передавать ли пакет
			bool transmit = true;

			// Обработчик пакета
			IPacketHandler* pHandler = NULL;

			// Обрабатываем пакет
			if (length > 2 && length < 6)
			{
				sendDebug("[0] length: " + std::to_string(length));
			}
			if (length >= 6)
			{
				// Расшифровываем пакет
				if (m_packet_encryptor.enabled()) {
					try {
						m_packet_encryptor.decrypt(const_cast<char*>(data + 6), (length - 6), decrypt_t::dec_cs);
					}
					catch (...) {
						printf("* [0] catch decrypt\n");
					}
				}

				// Получаем список обработчиков
				const CPacketHandlerManager& HandlerMgr = m_server->getClientPacketHandlers();

				// Устанавливаем данные объекту для чтения
				m_reader.setData(const_cast<char *>(data), length);
				m_reader.seek(0, seek_type_t::seek_begin);

				// Читаем заголовок
				uint16_t packet_size = m_reader.readUint16();
				uint32_t session = m_reader.readUint32();
				uint16_t packet_id = m_reader.readUint16();

				// Отладка пакетов
				//if (stall_server()->config().is_debug_enabled()) {

					//printf("C -> S Packet ID: %d, Packet Size: %d\n", packet_id, packet_size);

				//}
				
				// Проверим первый ли это пакет
				if (IsFirstPacket) {

					// Теперь уже не первый
					IsFirstPacket = false;

					// Если это не пакет авторизации
					if (packet_id != 431) {

						// Закроем соединение с клиентов
						m_client_socket->close();
						std::cout << "First packet no autorization!" << std::endl;
						return;

					}

				}

				// Проверяем пакет
				if (m_protection.enabled())
				{
					uint32_t packet_n = m_reader.readUint32();
				 
					if (!m_protection.check_packet(packet_n)) {

						if (packet_id == 431)
						{
							CWrongVersionPacket wrong_version_packet;
							sendPacket(m_server_socket, &wrong_version_packet);
						}

						CDisconnectPacket disconnect_packet(*this, "Protection");
						sendPacket(m_client_socket, &disconnect_packet);
						return;
					}
				}

				// Обрабатываем пакет
				if (HandlerMgr.has(packet_id))
				{

					pHandler = HandlerMgr.get(packet_id);

					// Убедимся, что обработчик существует
					if (pHandler) {

						pHandler->read(m_reader, *this);
						transmit = pHandler->handle(*this);

					}
					
				}
			}

			if (m_client_socket->connected() && transmit)
			{
				if (length >= 6)
				{
					// Восстанавливаем пакет
					if (m_protection.enabled())
					{
						length -= 4;
						unsigned short int new_length = htons(static_cast<u_short>(length));
						std::memcpy(const_cast<char *>(data + 8), (data + 12), length - 6);
						std::memcpy(const_cast<char *>(data), reinterpret_cast<char *>(&new_length), sizeof(new_length));
					}

					// Зашифровываем пакет
					if (m_packet_encryptor.enabled()) {
						try {
							m_packet_encryptor.encrypt(const_cast<char*>(data + 6), (length - 6), encrypt_t::enc_cs);
						}
						catch (...) {
							printf("* [2] catch encrypt\n");
						}
					}

					// Отправляем пакет
					m_client_socket->write(data, length);

					// Убедимся, что обработчик существует
					if (pHandler) {

						// Пост обработка  пакета
						pHandler->after_send(*this);
						// Пост очистка пакета
						pHandler->reset();

					}
					
				}
				//else
				//{
				setPingTime(GetTickCount64());
				//}
			}
		}
		catch (const binary_io_exception&) {
			//std::cout << "[C -> S] " << e.what() << std::endl;

			CDisconnectPacket disconnect_packet(*this, "binary_io_exception");
			sendPacket(m_client_socket, &disconnect_packet);

			m_client_socket->close();
		}
		catch (const packet_handler_mgr_exception&) {
			//std::cout << "[C -> S] " << e.what() << std::endl;

			CDisconnectPacket disconnect_packet(*this, "packet_handler_mgr_exception");
			sendPacket(m_client_socket, &disconnect_packet);

			m_client_socket->close();
		}
		catch (const std::runtime_error&) {
			//std::cout << "[C -> S] " << e.what() << std::endl;

			CDisconnectPacket disconnect_packet(*this, "runtime_error");
			sendPacket(m_client_socket, &disconnect_packet);

			m_client_socket->close();
		}
		catch (...) {
			//std::cout << "[C -> S] Unknown error while handling data from Game Client!" << std::endl;

			CDisconnectPacket disconnect_packet(*this, "unknown");
			sendPacket(m_client_socket, &disconnect_packet);
			
			m_client_socket->close();
		}
	}

	// Ошибка на сокете клиента
	void CPlayer::on_client_error(int errcode)
	{
		// Отладочная печать
		//std::cout << "Error on client socket!" << std::endl;
		//std::cout << "Error code: " << errcode << std::endl;
	}


	// ===============================================
	// Наблюдатель за клиентским сокетом
	// ===============================================

	// Подключены к серверу
	void CPlayer::on_server_connected()
	{
	}

	// Отключены от сервера
	void CPlayer::on_server_disconnected()
	{
		
		// Если игрок уже авторизовался
		if (!IsWaitAutorization()) {

			// Отключаем аккаунт
			m_server->account_disconnected(this);

		}
	
		// Отключаем игрока
		m_server->player_disconnected(this);
		// Закрываем клиентский сокет
		m_client_socket->close();

	}

	// Авторизация на сервере
	void CPlayer::on_server_login()
	{
		//std::stringstream message;
		//message << "joined the server (MAC: " << account().getMacAddress() << " version: " << account().getVersion() << ")";
		//sendDebug(message.str());

		m_server->account_connected(this);

	}

	// Прекращение авторизации на сервере
	void CPlayer::on_server_logout()
	{
		//m_server->account_disconnected(this);
	}

	// Получены данные от сервера
	void CPlayer::on_server_recived_data(const char *data, size_t length)
	{
		// ID пакета
		uint16_t packet_id = 0;

		try
		{
			// Передавать ли пакет
			bool transmit = true;

			// Обработчик пакета
			IPacketHandler* pHandler = NULL;

			// Обрабатываем пакет
			if (length > 2 && length < 6)
			{
				//sendDebug("[1] length: " + std::to_string(length));
			}
			if (length >= 6)
			{
				// Расшифровываем пакет
				if (m_packet_encryptor.enabled()) {
					try {
						m_packet_encryptor.decrypt(const_cast<char*>(data + 6), (length - 6), decrypt_t::dec_sc);
					}
					catch (...) {
						printf("* [3] catch decrypt\n");
					}
				}

				// Получаем список обработчиков
				const CPacketHandlerManager& HandlerMgr = m_server->getServerPacketHandlers();

				// Устанавливаем данные объекту для чтения
				m_reader.setData(const_cast<char *>(data), length);
				m_reader.seek(0, seek_type_t::seek_begin);

				// Читаем заголовок
				uint16_t packet_size = m_reader.readUint16();
				uint32_t session = m_reader.readUint32();
				packet_id = m_reader.readUint16();

				// Отладка пакетов
				//if (stall_server()->config().is_debug_enabled()) {

					//printf("S -> C Packet ID: %d, Packet Size: %d\n", packet_id, packet_size);

				//}
		
				// Обрабатываем пакет
				if (HandlerMgr.has(packet_id))
				{
					pHandler = HandlerMgr.get(packet_id);

					// Убедимся, что обработчик существует
					if (pHandler) {

						pHandler->read(m_reader, *this);
							transmit = pHandler->handle(*this);

					}
					
				}
			}

			if (m_server_socket->connected())
			{
				if (transmit && length >= 6)
				{
					// Зашифровываем пакет
					if (m_packet_encryptor.enabled() && packet_id != 931) {
						try {
							m_packet_encryptor.encrypt(const_cast<char*>(data + 6), (length - 6), encrypt_t::enc_sc);
						}
						catch (...) {
							printf("* [5] catch encrypt\n");
						}
					}

					// Отправляем пакет
					m_server_socket->write(data, length);

					// Убедимся, что обработчик существует
					if (pHandler) {

						// Пост обработка  пакета
						pHandler->after_send(*this);
						// Пост очистка пакета
						pHandler->reset();

					}

				}
			}

			// Отвечаем на пинг пакет от GateServer.exe
			if (length == 2)
			{
				unsigned short int ping = 0x0200;
				m_client_socket->write(reinterpret_cast<char *>(&ping), sizeof(ping));
			}
			
		}
		catch (const binary_io_exception&) {
			// std::cout << "[S -> C] " << e.what() << " Packet ID " << packet_id << std::endl;
			m_client_socket->close();
		}
		catch (const packet_handler_mgr_exception&) {
			// std::cout << "[S -> C] " << e.what() << std::endl;	
			m_client_socket->close();
		}
		catch (const std::runtime_error&) {
			// std::cout << "[S -> C] " << e.what() << std::endl;	
			m_client_socket->close();
		}
		catch (...) 
		{
			// std::cout << "[S -> C] Unknown error while handling data from GateServer!" << std::endl;
			m_client_socket->close();
		}
	}

	// Ошибка на сокете сервера
	void CPlayer::on_server_error(int errcode)
	{
		// Отладочная печать
		if (errcode == 10061)
		{
			on_server_disconnected();
		}

		 //std::cout << "Error on server socket!" << std::endl;
		 //std::cout << "Error code: " << errcode << std::endl;
	}

	// Перезайти на аккаунт
	void CPlayer::do_relogin()
	{
		struct timeval tv;

		tv.tv_sec = 0;
		tv.tv_usec = 100;
		evtimer_add(m_relogin_event, &tv);
	}

	// Переподключиться к серверу
	void CPlayer::relogin()
	{
		// Формируем логин пакет
		CLoginPacket login_packet;
		login_packet.setChapString(m_account.getChapString());
		login_packet.setNobill(m_account.getBillString());
		login_packet.setLogin(m_account.getLogin());
		login_packet.setPassword(m_account.getPassword());
		login_packet.setMacAddress(m_account.getMacAddress());
		login_packet.setIpAddress(m_server_socket->getIpAddress());
		login_packet.setFlag(m_account.getFlag());
		login_packet.setVersion(m_account.getVersion());

		// Отправляем логин пакет
		sendPacket(m_client_socket, &login_packet);
	}

	// Получить время пинга
	unsigned __int64 CPlayer::getPingTime() const
	{
		return m_ping_time;
	}

	// Установить время пинга
	void CPlayer::setPingTime(unsigned __int64 time)
	{
		m_ping_time = time;
	}

	// Получить время подключения
	unsigned __int64 CPlayer::getLoginTime() const
	{
		return m_login_time;
	}

	// Устанавливаем время подключения
	void CPlayer::setLoginTime(unsigned __int64 time)
	{
		m_login_time = time;
	}
	
	// Получить авторизировано ли соединение
	bool CPlayer::IsWaitAutorization() const
	{
		return isAutorization;
	}

	// Устанавливаем авторизировано ли соединение
	void CPlayer::setCheckAutorization(bool val)
	{
		isAutorization = val;
	
	}

}


