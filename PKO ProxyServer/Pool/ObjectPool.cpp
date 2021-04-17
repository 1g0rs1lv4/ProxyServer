#include "ObjectPool.h"

namespace PKO
{
	// Конструктор
	CObjectPool::CObjectPool(IObjectMaker *pMaker, size_t size) :
		m_pMaker(pMaker), m_size(size)
	{
		// Создаем объекты и добавляем их в стек
		for (size_t i = 0; i < size; i++) {
			m_Objects.push(pMaker->make());
		}
	}

	// Деструктор
	CObjectPool::~CObjectPool()
	{
		// Удаляем объекты из стека
		while (!m_Objects.empty())
		{
			delete m_Objects.top();
			m_Objects.pop();
		}

		// Удаляем создателя объектов
		if (m_pMaker != nullptr) {
			delete m_pMaker;
		}
	}

	// Взять объект из пула
	IPoolable *CObjectPool::acquire()
	{
		// Проверим, что в пуле есть объекты
		if (m_Objects.empty())
		{
			// Добавим в пул новые объекты
			for (size_t i = 0; i < 32; i++) {
				m_Objects.push(m_pMaker->make());
			}
		}

		// Берем объект с верхушки стека
		IPoolable *pObject = m_Objects.top();

		// Удаляем его из стека
		m_Objects.pop();

		// Отдаем клиенту
		return pObject;
	}

	// Вернуть объект в пул
	void CObjectPool::release(IPoolable *pObject)
	{
		pObject->reset();
		m_Objects.push(pObject);
	}
}