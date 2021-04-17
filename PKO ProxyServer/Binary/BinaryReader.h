#pragma once
#include "BaseBinaryIO.h"

namespace PKO
{
	class CBinaryReader : public CBaseBinaryIO
	{
		public:

			// �����������
			CBinaryReader();
			CBinaryReader(char *data, size_t size);

			// ����������
			virtual ~CBinaryReader();

			// ��������� ����
			ubyte_t readByte();

			// ��������� UInt16
			uint16_t readUint16();

			// ��������� UInt32
			uint32_t readUint32();

			// ��������� ������
			string_t readString();

			// ��������� ������ ����
			void readByteArray(ubyte_t *dst, size_t count);

		private:

			// ��������� ������
			void read(ubyte_t *dst, size_t n);
	};
}

