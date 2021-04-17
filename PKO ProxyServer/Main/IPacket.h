#pragma once

namespace PKO
{

	class CBinaryWriter;

	// ��������� ������
	class IPacket
	{
		public:

			// �������� ID ������
			virtual unsigned short int getId() const = 0;

			// �������� ����� � �����
			virtual void write(CBinaryWriter& Writer) = 0;
	};


}