#include "ObjectPool.h"

namespace PKO
{
	// �����������
	CObjectPool::CObjectPool(IObjectMaker *pMaker, size_t size) :
		m_pMaker(pMaker), m_size(size)
	{
		// ������� ������� � ��������� �� � ����
		for (size_t i = 0; i < size; i++) {
			m_Objects.push(pMaker->make());
		}
	}

	// ����������
	CObjectPool::~CObjectPool()
	{
		// ������� ������� �� �����
		while (!m_Objects.empty())
		{
			delete m_Objects.top();
			m_Objects.pop();
		}

		// ������� ��������� ��������
		if (m_pMaker != nullptr) {
			delete m_pMaker;
		}
	}

	// ����� ������ �� ����
	IPoolable *CObjectPool::acquire()
	{
		// ��������, ��� � ���� ���� �������
		if (m_Objects.empty())
		{
			// ������� � ��� ����� �������
			for (size_t i = 0; i < 32; i++) {
				m_Objects.push(m_pMaker->make());
			}
		}

		// ����� ������ � �������� �����
		IPoolable *pObject = m_Objects.top();

		// ������� ��� �� �����
		m_Objects.pop();

		// ������ �������
		return pObject;
	}

	// ������� ������ � ���
	void CObjectPool::release(IPoolable *pObject)
	{
		pObject->reset();
		m_Objects.push(pObject);
	}
}