#pragma once
#include <string>

namespace PKO
{

	// ����� ��� ���������� �������
	class CPasswordEncoder
	{
		public:

			// �����������
			CPasswordEncoder();

			// ����������
			~CPasswordEncoder();

			// ���������� ������ � ����� �����������
			void set_password(const std::string& password);
			void set_chap_string(const std::string& chap_string);

			// �������� ������ � ����� �����������
			const std::string& get_password() const;
			const std::string& get_chap_stirng() const;

			// ����������� ������
			void encode(char *encoded_password, unsigned short int &length);



		private:

			// ������ �� �������� �����������
			std::string m_chap_string;

			// ������
			std::string m_password;
	};


}