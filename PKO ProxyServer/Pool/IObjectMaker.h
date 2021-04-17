#pragma once
#include "IPoolable.h"

namespace PKO
{
	// ��������� ��� �������� ��������
	// ������� ����� ��������� � ����
	class IObjectMaker
	{
		public:
			// ������� ������
			virtual IPoolable *make() = 0;
	};
}
