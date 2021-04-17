#pragma once
#include "../../Main/IPacketHandler.h"
#include <string>
#include "../../Struct/stNetChangeChaPart.h"

namespace PKO
{
	// Обработчик пакета с запросом закрытия ларька
	// C -> S
	class CNewChaHandle : public IPacketHandler
	{
	public:

		// Конструктор
		CNewChaHandle();

		// Деструктор
		~CNewChaHandle();

		// Получить ID пакета
		virtual unsigned short int getId() const;

		// Прочитать пакет
		virtual void read(CBinaryReader& Reader, CPlayer& Player);

		// Обработать пакет
		virtual bool handle(CPlayer& Player);

		// Действие после отправки пакета
		virtual void after_send(CPlayer& Player);

		// Сбросить обработчик
		virtual void reset();

	private:

		// Запрещаем копирование
		CNewChaHandle(const CNewChaHandle&) = delete;
		CNewChaHandle& operator=(const CNewChaHandle&) = delete;

		std::string chaname;
		std::string birth;
		unsigned short int len;
		LOOK look;
	};
}

