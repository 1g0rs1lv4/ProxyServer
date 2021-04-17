#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ����� �������� ������ ����
	class CWrongNewChaPacket : public IPacket
	{
	public:

		// �����������
		CWrongNewChaPacket(unsigned short int error);

		// ����������
		~CWrongNewChaPacket();

		// �������� ID ������
		virtual unsigned short int getId() const;

		// �������� ����� � �����
		virtual void write(CBinaryWriter& Writer);

	private:

		// �������� �����������
		CWrongNewChaPacket(const CWrongNewChaPacket&) = delete;
		CWrongNewChaPacket& operator=(const CWrongNewChaPacket&) = delete;

		unsigned short int error_id;
	};
}



