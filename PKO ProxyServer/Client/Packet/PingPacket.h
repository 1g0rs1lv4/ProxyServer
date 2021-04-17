#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ���� �����
	// C -> S (GameServer)
	class CPingPacket : public IPacket
	{
		public:

			// �����������
			CPingPacket();

			// ����������
			~CPingPacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);

		private:

			// �������� �����������
			CPingPacket(const CPingPacket&) = delete;
			CPingPacket& operator=(const CPingPacket&) = delete;
	};
}

