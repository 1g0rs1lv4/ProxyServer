#pragma once

namespace PKO
{
	// ��������� �������, ������� ����� ��������� � ���
	class IPoolable
	{
		public:
			// �������� ��������� �������
			virtual void reset() = 0;
	};
}

