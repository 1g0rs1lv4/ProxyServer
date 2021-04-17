#include <fstream>
#include <algorithm>
#include "Settings.h"
#include <iostream>
#include "../../Class/Utils/Utils.h"

// Обработчик консоли
extern HANDLE handle;

// Напечатать цветом
extern void WriteColorText(HANDLE handle, std::string str, WORD color);

namespace PKO
{
	// Конструктор
	CSettings::CSettings() :
		m_listen_port(1973), m_player_pool_size(1024),
		m_gate_server_ip("127.0.0.1"), m_gate_server_port(1024),
		m_max_connect(500), m_wpe_protection(false), m_auto_close_on_empty(false), m_wpe_version(0),
		debug_enabled(false), m_max_stalls_per_ip(0),
		m_max_offline_trade_time(0), m_vessel_deed_id(3988), m_connect_interval(0)

		#if ModuleWeb 
				, webIp("127.0.0.1"), webPort(111), webKey("secretKey"), webEnable(false) 
		#endif

	{
		m_map_list.reserve(32);
	}

	// Деструктор
	CSettings::~CSettings()
	{

	}

	// Загрузить настройки из файла
	void CSettings::load(const std::string& path)
	{
		// Открываем файл
		std::ifstream cfg(path);
		if (!cfg.is_open()) {

			std::cout << "Can't open file with settings: ";
			WriteColorText(handle, path, 14);
			std::cout << "!" << std::endl;

			throw settings_exception("Error: settings file not found!");

		}

		// Читаем файл построчно
		std::string line, section, param, value;
		size_t line_counter = 0;

		while (std::getline(cfg, line))
		{
			// Считаем строки
			line_counter++;

			// Удаляем из строки лишние пробелы
			line = CUtils::TrimString(line);

			// Пропускаем пустые строки
			if (line.empty()) {
				continue;
			}

			// Пропускаем закомментированные строки
			if (line.find("//") == 0) {
				continue;
			}

			// Удаляем из строки комментарии
			line = CUtils::DeleteComments(line);

			// Получаем название секции
			if (line.front() == '[' && line.back() == ']')
			{
				section = CUtils::TrimString(line.substr(1, line.length() - 2));
				std::transform(section.begin(), section.end(), section.begin(), ::tolower);
			}
			else
			{
				// Получаем название параметра
				size_t eq_pos = line.find('=');
				if (eq_pos == std::string::npos)
				{
					// Ошибка синтаксиса
					throw settings_exception("Can't load settings, error at " +
						std::to_string(line_counter) + " line!");
				}

				param = CUtils::TrimString(line.substr(0, eq_pos));
				value = CUtils::TrimString(line.substr(eq_pos + 1, line.length() - 1));

				if (section == "toclient")
				{
					if (param == "port")
					{
						try {
							m_listen_port = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid listen port at line " + std::to_string(line_counter) + "!");
						}
					}
					else if (param == "pool_size")
					{
						try {
							m_player_pool_size = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid client pool size at line " + std::to_string(line_counter) + "!");
						}
					}
				}
				else if (section == "togate")
				{
					if (param == "host") {
						m_gate_server_ip = value;
					}
					else if (param == "port")
					{
						try {
							m_gate_server_port = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid gate server port at line " + std::to_string(line_counter) + "!");
						}
					}
				}
				else if (section == "maps")
				{
					if (param == "map") {
						m_map_list.push_back(value);
					}
				}
				else if (section == "proxy")
				{
					if (param == "max_connect")
					{

						try {
							m_max_connect = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid max connected at line " + std::to_string(line_counter) + "!");
						}

					}
					else if (param == "connect_interval")
					{

						try {
							m_connect_interval = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid connect interval at line " + std::to_string(line_counter) + "!");
						}

					}
				}
				else if (section == "protection")
				{
					if (param == "enabled") {

						m_wpe_protection = (value == "0") ? false : true;

					} 
					
					// Запрещаем менять версию
					/* else if (param == "version") {

						try {
							m_wpe_version = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid protection version at line " + std::to_string(line_counter) + "!");
						}

					} */
				}
				else if (section == "game")
				{
					if (param == "auto_close_on_empty") {
						m_auto_close_on_empty = (value == "0") ? false : true;
					}
					else if (param == "max_stalls_per_ip")
					{
						try {
							m_max_stalls_per_ip = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid limit offline stalls per ip at line " + std::to_string(line_counter) + "!");
						}
					}
					else if (param == "max_offline_trade_time")
					{
						try {
							m_max_offline_trade_time = static_cast<unsigned short int>(std::stoi(value)) * 1000;
						}
						catch (...) {
							throw settings_exception("Invalid max offline trade time at line " + std::to_string(line_counter) + "!");
						}
					}
					else if (param == "vessel_deed_id")
					{
						try {
							m_vessel_deed_id = static_cast<unsigned short int>(std::stoi(value));
						}
						catch (...) {
							throw settings_exception("Invalid Vessel Deed ID at line " + std::to_string(line_counter) + "!");
						}
					}
				}
				/*
				else if (section == "debug")
				{
					if (param == "enabled") {

						debug_enabled = (value == "0") ? false : true;
					}
				}
				*/
				#if ModuleWeb
				else if (section == "web")
				{
					
					if (param == "enabled") {

						webEnable = (value == "0") ? false : true;

					} else if (param == "host") {

						webIp = value;

					} else if (param == "port") {

						try {

							webPort = static_cast<unsigned short int>(std::stoi(value));

						} catch (...) {

							throw settings_exception("Invalid web server port at line " + std::to_string(line_counter) + "!");
						
						}

					} else if (param == "key") {

						try {

							webKey = value;

						} catch (...) {

							throw settings_exception("Invalid web server key at line " + std::to_string(line_counter) + "!");

						}

					}
					
				}
				#endif
			}
		}

		// Закрываем файл
		cfg.close();
	}

	// Получить настройки
	unsigned short int CSettings::listen_port() const
	{
		return m_listen_port;
	}

	void CSettings::setListenPort(unsigned short int port)
	{
		m_listen_port = port;
	}

	unsigned short int CSettings::gate_server_port() const
	{
		return m_gate_server_port;
	}

	const std::string& CSettings::gate_server_ip() const
	{
		return m_gate_server_ip;
	}

	unsigned int CSettings::player_pool_size() const
	{
		return m_player_pool_size;
	}

	bool CSettings::wpe_protection() const
	{
		return m_wpe_protection;
	}

	unsigned short int CSettings::wpe_version() const {

		return m_wpe_version;

	}

	bool CSettings::auto_close_on_empty() const
	{
		return m_auto_close_on_empty;
	}

	bool CSettings::is_debug_enabled() const
	{
		return debug_enabled;
	}

	const map_list_t& CSettings::map_list() const
	{
		return m_map_list;
	}

	unsigned int CSettings::max_stalls_per_ip() const
	{
		return m_max_stalls_per_ip;
	}

	unsigned int CSettings::max_offline_trade_time() const
	{
		return m_max_offline_trade_time;
	}

	unsigned int CSettings::vessel_deed_id() const
	{
		return m_vessel_deed_id;
	}

	unsigned int CSettings::max_connect() const
	{
		return m_max_connect;
	}

	unsigned int CSettings::connect_interval() const
	{
		return m_connect_interval;
	}

	#if ModuleWeb

		std::string CSettings::web_get_ip() const {

			return webIp;

		}

		int CSettings::web_get_port() const {

			return webPort;

		}

		std::string CSettings::web_get_key() const {

			return webKey;

		}

		bool CSettings::isWebEnable() const {

			return webEnable;

		}

	#endif

}

