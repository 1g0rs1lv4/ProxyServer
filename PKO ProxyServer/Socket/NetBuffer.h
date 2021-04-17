#pragma once

namespace PKO
{
	// ������� �����
	class CNetBuffer
	{
		public:

			// �����������
			CNetBuffer(size_t size);

			// ����������
			~CNetBuffer();

			// �������� ������ � �����
			void add(const char *data, size_t length);

			// ������� ������ �� ������
			void remove(size_t length);

			// �������� �����
			void clear();

			// �������� ��������� �� ������
			const char *data() const;

			// �������� ������ ������
			size_t size() const;

			// �������� ����� ������
			size_t length() const;

			// ���������� ����� ������
			void set_length(size_t length);

		private:

			// ������ ������
			size_t m_size;

			// ����� ������
			size_t m_length;

			// �����
			char *m_data;
	};

}
