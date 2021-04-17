#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// ���������� ������ ���������� �� �������
	// C -> S
	class CDisconnectHandler : public IPacketHandler
	{
		public:

			// �����������
			CDisconnectHandler();

			// ����������
			~CDisconnectHandler();

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
			CDisconnectHandler(const CDisconnectHandler&) = delete;
			CDisconnectHandler& operator=(const CDisconnectHandler&) = delete;
	};


}