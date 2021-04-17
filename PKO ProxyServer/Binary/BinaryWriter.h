#pragma once
#include "BaseBinaryIO.h"

namespace PKO
{
	class CBinaryWriter : public CBaseBinaryIO
	{
		public:

			// Конструктор
			CBinaryWriter();
			CBinaryWriter(char *data, size_t size);

			// Деструктор
			virtual ~CBinaryWriter();

			// Записать байт
			void writeByte(ubyte_t c);

			// Записать UInt16
			void writeUint16(uint16_t n);

			// Записать UInt32
			void writeUint32(uint32_t n);

			// Записать строку
			void writeString(const string_t& String);

			// Записать массив байт
			void writeByteArray(ubyte_t *buffer, size_t count);


		private:

			// Запрещаем копирование
			CBinaryWriter(const CBinaryWriter&) = delete;
			CBinaryWriter& operator=(const CBinaryWriter&) = delete;
	
			// Записать данные
			void write(const ubyte_t *data, size_t n);

	};
}