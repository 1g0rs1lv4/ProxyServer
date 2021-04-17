#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// ���������� ��������� ����������
	// S -> C
	class CBeginSeeHandler : public IPacketHandler
	{
		public:

			// �����������
			CBeginSeeHandler();

			// ����������
			~CBeginSeeHandler();

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
			CBeginSeeHandler(const CBeginSeeHandler&) = delete;
			CBeginSeeHandler& operator=(const CBeginSeeHandler&) = delete;

			// �� ���������
			int cha_id;
			// �� ������
			int model_id;

			// ������ ��������
			CPlayer* findPlayer;

	};

}
