#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ����� �������� ������ ����
	class CWrongVersionPacket : public IPacket
	{
		public:

			// �����������
			CWrongVersionPacket();

			// ����������
			~CWrongVersionPacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);

		private:

			// �������� �����������
			CWrongVersionPacket(const CWrongVersionPacket&) = delete;
			CWrongVersionPacket& operator=(const CWrongVersionPacket&) = delete;
	};
}



