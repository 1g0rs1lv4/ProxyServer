#pragma once
#include "BaseBinaryIO.h"

namespace PKO
{
	class CBinaryWriter : public CBaseBinaryIO
	{
		public:

			// �����������
			CBinaryWriter();
			CBinaryWriter(char *data, size_t size);

			// ����������
			virtual ~CBinaryWriter();

			// �������� ����
			void writeByte(ubyte_t c);

			// �������� UInt16
			void writeUint16(uint16_t n);

			// �������� UInt32
			void writeUint32(uint32_t n);

			// �������� ������
			void writeString(const string_t& String);

			// �������� ������ ����
			void writeByteArray(ubyte_t *buffer, size_t count);


		private:

			// ��������� �����������
			CBinaryWriter(const CBinaryWriter&) = delete;
			CBinaryWriter& operator=(const CBinaryWriter&) = delete;
	
			// �������� ������
			void write(const ubyte_t *data, size_t n);

	};
}