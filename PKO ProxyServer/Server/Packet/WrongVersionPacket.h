#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пакет неверной версии игры
	class CWrongVersionPacket : public IPacket
	{
		public:

			// Конструктор
			CWrongVersionPacket();

			// Деструктор
			~CWrongVersionPacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);

		private:

			// Запретим копирование
			CWrongVersionPacket(const CWrongVersionPacket&) = delete;
			CWrongVersionPacket& operator=(const CWrongVersionPacket&) = delete;
	};
}



