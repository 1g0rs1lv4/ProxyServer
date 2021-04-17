#pragma once

namespace PKO
{
	class CBinaryReader;
	class CPlayer;

	// ��������� ����������� �������
	class IPacketHandler
	{
		public:

			// �������� ID ������
			virtual unsigned short int getId() const = 0;

			// ��������� �����
			virtual void read(CBinaryReader& Reader, CPlayer& pPlayer) = 0;

			// ���������� �����
			virtual bool handle(CPlayer& pPlayer) = 0;

			// �������� ����� �������� ������
			virtual void after_send(CPlayer& pPlayer) = 0;

			// �������� ����������
			virtual void reset() = 0;
	};
}


