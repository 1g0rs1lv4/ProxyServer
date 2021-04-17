#pragma once
#include "../../Main/IPacket.h"

namespace PKO
{

	// Пакет неверной версии игры
	class CWrongLoginPacket : public IPacket
	{
	public:

		// Конструктор
		CWrongLoginPacket();

		// Деструктор
		~CWrongLoginPacket();

		// Получить ID пакета
		virtual unsigned short int getId() const;

		// Записать пакет в буфер
		virtual void write(CBinaryWriter& Writer);

	private:

		// Запретим копирование
		CWrongLoginPacket(const CWrongLoginPacket&) = delete;
		CWrongLoginPacket& operator=(const CWrongLoginPacket&) = delete;
	};
}



