#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	class CSysInfoHandler : public IPacketHandler
	{
		public:

			// �����������
			CSysInfoHandler();

			// ����������
			~CSysInfoHandler();

			// �������� ID ������
			virtual unsigned short int getId() const;

			// ��������� �����
			virtual void read(CBinaryReader& Reader, CPlayer& Player);

			// ���������� �����
			virtual bool handle(CPlayer& Player);

			// �������� �����
			virtual void reset();

		private:
			
			// ��������� �����������
			CSysInfoHandler(const CSysInfoHandler&) = delete;
			CSysInfoHandler& operator=(const CSysInfoHandler&) = delete;

			// ������ � ����������
			std::string m_message;

	};

}
