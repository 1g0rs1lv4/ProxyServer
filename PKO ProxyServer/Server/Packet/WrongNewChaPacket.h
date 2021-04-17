#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пакет неверной версии игры
	class CWrongNewChaPacket : public IPacket
	{
	public:

		// Конструктор
		CWrongNewChaPacket(unsigned short int error);

		// Деструктор
		~CWrongNewChaPacket();

		// Получить ID пакета
		virtual unsigned short int getId() const;

		// Записать пакет в буфер
		virtual void write(CBinaryWriter& Writer);

	private:

		// Запретим копирование
		CWrongNewChaPacket(const CWrongNewChaPacket&) = delete;
		CWrongNewChaPacket& operator=(const CWrongNewChaPacket&) = delete;

		unsigned short int error_id;
	};
}



