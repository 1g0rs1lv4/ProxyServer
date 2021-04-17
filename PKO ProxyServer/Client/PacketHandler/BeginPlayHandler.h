#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// Обработчик пакета входа на персонажа
	// C -> S
	class CBeginPlayHandler : public IPacketHandler
	{
	public:

		// Конструктор
		CBeginPlayHandler();

		// Деструктор
		~CBeginPlayHandler();

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
		CBeginPlayHandler(const CBeginPlayHandler&) = delete;
		CBeginPlayHandler& operator=(const CBeginPlayHandler&) = delete;

		// Выбранный персонаж
		std::string selectCha;

	};

}