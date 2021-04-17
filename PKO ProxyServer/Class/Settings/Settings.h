#pragma once
#include <string>
#include <vector>
#include <stdexcept>

#define ModuleWeb false
#define ModuleAntiDBG false

namespace PKO
{

	// ��� ������ ����, �� ������� �������� �������-������
	typedef std::vector<std::string> map_list_t;

	// ����� ����������
	class settings_exception : public std::runtime_error
	{
		public:
			settings_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~settings_exception() { }
	};

	// ����� �������� ������� �������-�������
	class CSettings
	{
		public:

			// �����������
			CSettings();

			// ����������
			~CSettings();

			// ��������� ��������� �� �����
			void load(const std::string& path);

			// ���������� ����
			void setListenPort(unsigned short int port);

			// �������� ���������
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

				// ��������� ��� �������
				std::string web_get_ip() const;
				int web_get_port() const;
				std::string web_get_key() const;
				bool isWebEnable() const;

			#endif

		private:

			// �������� �����������
			CSettings(const CSettings&) = delete;
			CSettings& operator=(const CSettings&) = delete;

			// ���� ��� ����������� ��������
			// Game.exe <-> Proxy Server.exe
			unsigned short int m_listen_port;

			// ��������� ������ ���� �������
			unsigned int m_player_pool_size;

			// IP ����� GateServer.exe
			std::string m_gate_server_ip;

			// ���� GateServer.exe
			unsigned short int m_gate_server_port;

			// ������ ����, �� ������� ��������� ������
			// �������-�������
			map_list_t m_map_list;

			// �������� �� ������ �� WPE/RPE
			bool m_wpe_protection;

			// ������ ������ Wpe/Rpe
			unsigned short int m_wpe_version;

			// ������������� ��������� ������ ������
			bool m_auto_close_on_empty;

			// �������� �� �������
			bool debug_enabled;

			// ���������� ������� � ������ IP
			unsigned int m_max_stalls_per_ip;

			// ������������ ����� ��������
			unsigned int m_max_offline_trade_time;

			// ���� HTTP-�������
			std::string m_http_key;

			// ID �������� ������ �� �����
			unsigned int m_vessel_deed_id;

			// ������������ ���-�� ���������� �� ��������
			unsigned int m_max_connect;

			// ���������� ����� ������������
			unsigned int m_connect_interval;

			#if ModuleWeb

				// Ip ���-�������
				std::string webIp;
				// ���� ���-�������
				int webPort;
				// ���� ���-�������
				std::string webKey;
				// ������� �� ���-������
				bool webEnable;
			
			#endif

	};


}