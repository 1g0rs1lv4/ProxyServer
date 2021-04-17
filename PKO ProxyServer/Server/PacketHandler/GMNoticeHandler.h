#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� New GMNotice
	// S -> C
	class CGMNotice : public IPacketHandler
	{
	public:

		// �����������
		CGMNotice();

		// ����������
		~CGMNotice();
			
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
		CGMNotice(const CGMNotice&) = delete;
		CGMNotice& operator=(const CGMNotice&) = delete;

		// ���������
		std::string m_message;

	};

}
