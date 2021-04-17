#pragma once
#include <stack>
#include <stdexcept>
#include "IObjectMaker.h"

namespace PKO
{
	// Определим класс исключения для пула объектв
	class object_pool_exception : public std::runtime_error {
		public:
			object_pool_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~object_pool_exception() { }
	};

	// Пул объектов
	class CObjectPool
	{
		public:

			// Конструктор
			CObjectPool(IObjectMaker *pMaker, size_t size);

			// Деструктор
			~CObjectPool();

			// Взять объект из пула
			IPoolable *acquire();

			// Вернуть объект в пул
			void release(IPoolable *pObject);

		private:
			
			// Запрещаем копирование
			CObjectPool(const CObjectPool&) = delete;
			CObjectPool& operator=(const CObjectPool&) = delete;

			// Создатель объектов
			IObjectMaker *m_pMaker;

			// Размер пула
			size_t m_size;

			// Хранилище объектов
			std::stack<IPoolable *> m_Objects;
	};

}
