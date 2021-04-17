#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пакет неверной версии игры
	class CCreatePasswordPacket : public IPacket
	{
	public:

		// Конструктор
		CCreatePasswordPacket();

		// Деструктор
		~CCreatePasswordPacket();

		// Получить ID пакета
		virtual unsigned short int getId() const;

		// Записать пакет в буфер
		virtual void write(CBinaryWriter& Writer);

	private:

		// Запретим копирование
		CCreatePasswordPacket(const CCreatePasswordPacket&) = delete;
		CCreatePasswordPacket& operator=(const CCreatePasswordPacket&) = delete;
	};
}


