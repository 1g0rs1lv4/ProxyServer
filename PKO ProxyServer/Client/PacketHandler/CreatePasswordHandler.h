#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ����� ������������ ������
	// C -> S
	class CCreatePasswordHandler : public IPacketHandler
	{
		public:

			// �����������
			CCreatePasswordHandler();

			// ����������
			~CCreatePasswordHandler();

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

			// �������� �����������
			CCreatePasswordHandler(const CCreatePasswordHandler&) = delete;
			CCreatePasswordHandler& operator=(const CCreatePasswordHandler&) = delete;

			std::string szPassword;
	};
}