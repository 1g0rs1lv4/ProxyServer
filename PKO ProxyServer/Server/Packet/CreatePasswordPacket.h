#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ����� �������� ������ ����
	class CCreatePasswordPacket : public IPacket
	{
	public:

		// �����������
		CCreatePasswordPacket();

		// ����������
		~CCreatePasswordPacket();

		// �������� ID ������
		virtual unsigned short int getId() const;

		// �������� ����� � �����
		virtual void write(CBinaryWriter& Writer);

	private:

		// �������� �����������
		CCreatePasswordPacket(const CCreatePasswordPacket&) = delete;
		CCreatePasswordPacket& operator=(const CCreatePasswordPacket&) = delete;
	};
}


