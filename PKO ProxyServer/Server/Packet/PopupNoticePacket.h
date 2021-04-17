#pragma once
#include <string>
#include "../../Main/IPacket.h"


namespace PKO
{
	class CPopupNoticePacket : public IPacket
	{
		public:

			CPopupNoticePacket(const std::string& message);

			~CPopupNoticePacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);


		private:

			// �������� �����������
			CPopupNoticePacket(const CPopupNoticePacket&) = delete;
			CPopupNoticePacket& operator=(const CPopupNoticePacket&) = delete;
			
			// ���������
			std::string m_message;
	
	};
}

