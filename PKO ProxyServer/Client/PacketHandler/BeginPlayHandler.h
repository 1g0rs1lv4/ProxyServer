#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// ���������� ������ ����� �� ���������
	// C -> S
	class CBeginPlayHandler : public IPacketHandler
	{
	public:

		// �����������
		CBeginPlayHandler();

		// ����������
		~CBeginPlayHandler();

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
		CBeginPlayHandler(const CBeginPlayHandler&) = delete;
		CBeginPlayHandler& operator=(const CBeginPlayHandler&) = delete;

		// ��������� ��������
		std::string selectCha;

	};

}