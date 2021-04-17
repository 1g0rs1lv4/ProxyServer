#pragma once
#include <string>
#include "../../Main/IPacket.h"


namespace PKO
{
	class CGMNoticePacket : public IPacket
	{
		public:

			CGMNoticePacket();

			~CGMNoticePacket();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer);

			// ���������� ���������
			void setMessage(const std::string& message);

		private:

			// �������� �����������
			CGMNoticePacket(const CGMNoticePacket&) = delete;
			CGMNoticePacket& operator=(const CGMNoticePacket&) = delete;
			
			// ���������
			std::string m_message;
	
	};
}

