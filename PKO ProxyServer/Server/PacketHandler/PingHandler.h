#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ������� �� ����
	// S -> C
	class CPingHandler : public IPacketHandler
	{
		public:

			// �����������
			CPingHandler();

			// ����������
			~CPingHandler();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// ��������� �����
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// ���������� �����
			virtual bool handle(CPlayer& Player);

			// �������� ����� �������� ������
			virtual void after_send(CPlayer& Player);

			// �������� ����������
			virtual void reset();

		private:
			
			// �������� �����������
			CPingHandler(const CPingHandler&) = delete;
			CPingHandler& operator=(const CPingHandler&) = delete;


	};

}
