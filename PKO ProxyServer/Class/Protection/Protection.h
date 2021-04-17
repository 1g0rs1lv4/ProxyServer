#pragma once

namespace PKO
{

	// ����� ������
	class CProtection
	{
		public:

			// �����������
			CProtection();

			// ����������
			~CProtection();

			// ���������������� ������
			void init(bool enabled, unsigned short int ver);

			// ��������� �����
			bool check_packet(unsigned int n);

			// ��������� �����
			unsigned short int getVersion() { return m_ver; };

			// �������� �� ������
			bool enabled() const;

		private:

			// �������� �����������
			CProtection(const CProtection&) = delete;
			CProtection& operator=(const CProtection&) = delete;


			// �������� �� ������
			bool m_enabled;

			// ������ ������
			unsigned short int m_ver;

			// ������� �������
			unsigned int m_packet_counter;
	};

}
