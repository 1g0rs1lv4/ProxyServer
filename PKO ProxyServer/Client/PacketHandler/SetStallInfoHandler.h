#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"
#include "../../Class/SetStall/SetStall.h"

namespace PKO
{
	// ���������� ������ � ����������� � ������
	// C -> S
	class CSetStallInfoHandler : public IPacketHandler
	{
		public:

			// �����������
			CSetStallInfoHandler();

			// ����������
			~CSetStallInfoHandler();

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
			CSetStallInfoHandler(const CSetStallInfoHandler&) = delete;
			CSetStallInfoHandler& operator=(const CSetStallInfoHandler&) = delete;

			// �������� ������
			std::string m_name;

			// ���������� ������
			unsigned int m_slot_number;

			// ������
			SStallCell m_cells[18];
	};

}
