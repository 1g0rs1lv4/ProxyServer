#pragma once

namespace PKO
{
	class CBinaryReader;
	class CPlayer;

	// Интерфейс обработчика пакетов
	class IPacketHandler
	{
		public:

			// Получить ID пакета
			virtual unsigned short int getId() const = 0;

			// Прочитать пакет
			virtual void read(CBinaryReader& Reader, CPlayer& pPlayer) = 0;

			// Обработать пакет
			virtual bool handle(CPlayer& pPlayer) = 0;

			// Действие после отправки пакета
			virtual void after_send(CPlayer& pPlayer) = 0;

			// Сбросить обработчик
			virtual void reset() = 0;
	};
}


