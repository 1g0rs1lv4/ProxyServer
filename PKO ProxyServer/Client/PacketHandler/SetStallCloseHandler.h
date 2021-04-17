#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ������ � �������� �������� ������
	// C -> S
	class CSetStallCloseHandler : public IPacketHandler
	{
		public:

			// �����������
			CSetStallCloseHandler();

			// ����������
			~CSetStallCloseHandler();

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
			CSetStallCloseHandler(const CSetStallCloseHandler&) = delete;
			CSetStallCloseHandler& operator=(const CSetStallCloseHandler&) = delete;

	};
}

