#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пинг пакет
	// C -> S (GameServer)
	class CPingPacket : public IPacket
	{
		public:

			// Конструктор
			CPingPacket();

			// Деструктор
			~CPingPacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);

		private:

			// Запретим копирование
			CPingPacket(const CPingPacket&) = delete;
			CPingPacket& operator=(const CPingPacket&) = delete;
	};
}

