#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// ����� �������� ������ ����
	class CWrongLoginPacket : public IPacket
	{
	public:

		// �����������
		CWrongLoginPacket();

		// ����������
		~CWrongLoginPacket();

		// �������� ID ������
		virtual unsigned short int getId() const;

		// �������� ����� � �����
		virtual void write(CBinaryWriter& Writer);

	private:

		// �������� �����������
		CWrongLoginPacket(const CWrongLoginPacket&) = delete;
		CWrongLoginPacket& operator=(const CWrongLoginPacket&) = delete;
	};
}



