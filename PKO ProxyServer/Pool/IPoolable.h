#pragma once

namespace PKO
{
	// Интерфейс объекта, который можно поместить в пул
	class IPoolable
	{
		public:
			// Сбросить состояние объекта
			virtual void reset() = 0;
	};
}

