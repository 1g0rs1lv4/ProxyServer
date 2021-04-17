#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пакет неверной версии игры
	class CUpdatePasswordPacket : public IPacket
	{
	public:

		// Конструктор
		CUpdatePasswordPacket();

		// Деструктор
		~CUpdatePasswordPacket();

		// Получить ID пакета
		virtual unsigned short int getId() const;

		// Записать пакет в буфер
		virtual void write(CBinaryWriter& Writer);

	private:

		// Запретим копирование
		CUpdatePasswordPacket(const CUpdatePasswordPacket&) = delete;
		CUpdatePasswordPacket& operator=(const CUpdatePasswordPacket&) = delete;
	};
}


