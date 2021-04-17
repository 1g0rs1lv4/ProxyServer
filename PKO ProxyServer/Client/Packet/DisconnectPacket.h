#pragma once
#include "../../Main/IPacket.h"
#include "../../Class/Player/Player.h"
#include <string>

namespace PKO
{

	// Пакет отключения от сервера
	// C -> S
	class CDisconnectPacket : public IPacket
	{
		public:

			// Конструктор
			CDisconnectPacket(CPlayer& Player, const std::string reason);

			// Деструктор
			~CDisconnectPacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);

		private:

			// Запретим копирование
			CDisconnectPacket(const CDisconnectPacket&) = delete;
			CDisconnectPacket& operator=(const CDisconnectPacket&) = delete;
	};
}

