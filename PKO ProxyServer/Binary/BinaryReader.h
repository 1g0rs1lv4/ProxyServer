#pragma once
#include "BaseBinaryIO.h"

namespace PKO
{
	class CBinaryReader : public CBaseBinaryIO
	{
		public:

			// Конструктор
			CBinaryReader();
			CBinaryReader(char *data, size_t size);

			// Деструктор
			virtual ~CBinaryReader();

			// Прочитать байт
			ubyte_t readByte();

			// Прочитать UInt16
			uint16_t readUint16();

			// Прочитать UInt32
			uint32_t readUint32();

			// Прочитать строку
			string_t readString();

			// Прочитать массив байт
			void readByteArray(ubyte_t *dst, size_t count);

		private:

			// Прочитать данные
			void read(ubyte_t *dst, size_t n);
	};
}

