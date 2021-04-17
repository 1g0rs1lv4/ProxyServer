#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ����� ������������ ������
	// C -> S
	class �ChangePasswordHandler : public IPacketHandler
	{
	public:

		// �����������
		�ChangePasswordHandler();

		// ����������
		~�ChangePasswordHandler();

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
		�ChangePasswordHandler(const �ChangePasswordHandler&) = delete;
		�ChangePasswordHandler& operator=(const �ChangePasswordHandler&) = delete;

		std::string szOld;
		std::string szPassword;
	};
}