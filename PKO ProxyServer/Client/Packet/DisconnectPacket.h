#pragma once
#include "../../Main/IPacket.h"
#include "../../Class/Player/Player.h"
#include <string>

namespace PKO
{

	// ����� ���������� �� �������
	// C -> S
	class CDisconnectPacket : public IPacket
	{
		public:

			// �����������
			CDisconnectPacket(CPlayer& Player, const std::string reason);

			// ����������
			~CDisconnectPacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);

		private:

			// �������� �����������
			CDisconnectPacket(const CDisconnectPacket&) = delete;
			CDisconnectPacket& operator=(const CDisconnectPacket&) = delete;
	};
}

