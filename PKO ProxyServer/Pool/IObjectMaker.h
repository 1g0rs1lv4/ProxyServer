#pragma once
#include "IPoolable.h"

namespace PKO
{
	// Интерфейс для создания объектов
	// которые могут храниться в пуле
	class IObjectMaker
	{
		public:
			// Создать объект
			virtual IPoolable *make() = 0;
	};
}
