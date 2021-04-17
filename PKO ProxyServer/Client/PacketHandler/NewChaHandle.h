#pragma once
#include "../../Main/IPacketHandler.h"
#include <string>
#include "../../Struct/stNetChangeChaPart.h"

namespace PKO
{
	// ���������� ������ � �������� �������� ������
	// C -> S
	class CNewChaHandle : public IPacketHandler
	{
	public:

		// �����������
		CNewChaHandle();

		// ����������
		~CNewChaHandle();

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

		// ��������� �����������
		CNewChaHandle(const CNewChaHandle&) = delete;
		CNewChaHandle& operator=(const CNewChaHandle&) = delete;

		std::string chaname;
		std::string birth;
		unsigned short int len;
		LOOK look;
	};
}

