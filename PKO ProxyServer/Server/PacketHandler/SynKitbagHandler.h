#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	class CSynKitbagHandler : public IPacketHandler
	{
		public:

			//	�����������
			CSynKitbagHandler();

			// ����������
			~CSynKitbagHandler();

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
			CSynKitbagHandler(const CSynKitbagHandler&) = delete;
			CSynKitbagHandler& operator=(const CSynKitbagHandler&) = delete;

			// ID ���������
			unsigned int m_cha_id;

			// ����� ������ ���������
			unsigned int m_new_size;
	};
};

