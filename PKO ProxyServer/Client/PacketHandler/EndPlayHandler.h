#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// ���������� ������ ������ �� ����� ���������
	// C -> S
	class CEndPlayHandler : public IPacketHandler
	{
		public:

			// �����������
			CEndPlayHandler();

			// ����������
			~CEndPlayHandler();

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
			CEndPlayHandler(const CEndPlayHandler&) = delete;
			CEndPlayHandler& operator=(const CEndPlayHandler&) = delete;

	};

}