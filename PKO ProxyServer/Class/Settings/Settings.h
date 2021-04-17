#pragma once
#include <string>
#include <vector>
#include <stdexcept>

#define ModuleWeb false
#define ModuleAntiDBG false

namespace PKO
{

	// Тип списка карт, на которых работают оффлайн-ларьки
	typedef std::vector<std::string> map_list_t;

	// Класс исключения
	class settings_exception : public std::runtime_error
	{
		public:
			settings_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~settings_exception() { }
	};

	// Класс настроек сервера оффлайн-ларьков
	class CSettings
	{
		public:

			// Конструктор
			CSettings();

			// Деструктор
			~CSettings();

			// Загрузить настройки из файла
			void load(const std::string& path);

			// Установить порт
			void setListenPort(unsigned short int port);

			// Получить настройки
			unsigned short int listen_port() const;
			unsigned short int gate_server_port() const;
			const std::string& gate_server_ip() const;
			unsigned int player_pool_size() const;
			bool wpe_protection() const;
			unsigned short int wpe_version() const;
			bool auto_close_on_empty() const;
			bool is_debug_enabled() const;
			const map_list_t& map_list() const;
			unsigned int max_stalls_per_ip() const;
			unsigned int max_offline_trade_time() const;
			unsigned int vessel_deed_id() const;
			unsigned int max_connect() const;
			unsigned int connect_interval() const;
			
			#if ModuleWeb

				// Настройки веб сервера
				std::string web_get_ip() const;
				int web_get_port() const;
				std::string web_get_key() const;
				bool isWebEnable() const;

			#endif

		private:

			// Запретим копирование
			CSettings(const CSettings&) = delete;
			CSettings& operator=(const CSettings&) = delete;

			// Порт для подключения клиентов
			// Game.exe <-> Proxy Server.exe
			unsigned short int m_listen_port;

			// Начальный размер пула игроков
			unsigned int m_player_pool_size;

			// IP адрес GateServer.exe
			std::string m_gate_server_ip;

			// Порт GateServer.exe
			unsigned short int m_gate_server_port;

			// Список карт, на которых разрешена работа
			// оффлайн-ларьков
			map_list_t m_map_list;

			// Включена ли защита от WPE/RPE
			bool m_wpe_protection;

			// Версия защиты Wpe/Rpe
			unsigned short int m_wpe_version;

			// Автоматически закрывать пустые ларьки
			bool m_auto_close_on_empty;

			// Включена ли отладка
			bool debug_enabled;

			// Количество ларьков с одного IP
			unsigned int m_max_stalls_per_ip;

			// Максимальное время торговли
			unsigned int m_max_offline_trade_time;

			// Ключ HTTP-сервера
			std::string m_http_key;

			// ID предмета купчая на судно
			unsigned int m_vessel_deed_id;

			// Максимальное кол-во соединений от клиентов
			unsigned int m_max_connect;

			// Промежуток между соединениями
			unsigned int m_connect_interval;

			#if ModuleWeb

				// Ip веб-сервера
				std::string webIp;
				// Порт веб-сервера
				int webPort;
				// Ключ веб-сервера
				std::string webKey;
				// Включен ли веб-сервер
				bool webEnable;
			
			#endif

	};


}