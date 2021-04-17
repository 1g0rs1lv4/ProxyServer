#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ������ �� ������� � ����� � �������� �����������
	// S -> C
	class CChapStringHandler : public IPacketHandler
	{
		public:

			// �����������
			CChapStringHandler();

			// ����������
			~CChapStringHandler();

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
			CChapStringHandler(const CChapStringHandler&) = delete;
			CChapStringHandler& operator=(const CChapStringHandler&) = delete;

			// ������ �� �������� �����������
			std::string m_chap_string;
	};

}
