#pragma once

namespace PKO
{

	class CBinaryWriter;

	// Интерфейс пакета
	class IPacket
	{
		public:

			// Получить ID пакета
			virtual unsigned short int getId() const = 0;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer) = 0;
	};


}