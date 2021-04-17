#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ����� �������� ������ ����
	class CUpdatePasswordPacket : public IPacket
	{
	public:

		// �����������
		CUpdatePasswordPacket();

		// ����������
		~CUpdatePasswordPacket();

		// �������� ID ������
		virtual unsigned short int getId() const;

		// �������� ����� � �����
		virtual void write(CBinaryWriter& Writer);

	private:

		// �������� �����������
		CUpdatePasswordPacket(const CUpdatePasswordPacket&) = delete;
		CUpdatePasswordPacket& operator=(const CUpdatePasswordPacket&) = delete;
	};
}


