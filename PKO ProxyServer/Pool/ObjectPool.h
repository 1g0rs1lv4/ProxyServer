#pragma once
#include <stack>
#include <stdexcept>
#include "IObjectMaker.h"

namespace PKO
{
	// ��������� ����� ���������� ��� ���� �������
	class object_pool_exception : public std::runtime_error {
		public:
			object_pool_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~object_pool_exception() { }
	};

	// ��� ��������
	class CObjectPool
	{
		public:

			// �����������
			CObjectPool(IObjectMaker *pMaker, size_t size);

			// ����������
			~CObjectPool();

			// ����� ������ �� ����
			IPoolable *acquire();

			// ������� ������ � ���
			void release(IPoolable *pObject);

		private:
			
			// ��������� �����������
			CObjectPool(const CObjectPool&) = delete;
			CObjectPool& operator=(const CObjectPool&) = delete;

			// ��������� ��������
			IObjectMaker *m_pMaker;

			// ������ ����
			size_t m_size;

			// ��������� ��������
			std::stack<IPoolable *> m_Objects;
	};

}
