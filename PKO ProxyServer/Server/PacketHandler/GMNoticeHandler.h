#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик New GMNotice
	// S -> C
	class CGMNotice : public IPacketHandler
	{
	public:

		// Конструктор
		CGMNotice();

		// Деструктор
		~CGMNotice();
			
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

		// Запретим копирование
		CGMNotice(const CGMNotice&) = delete;
		CGMNotice& operator=(const CGMNotice&) = delete;

		// Сообщение
		std::string m_message;

	};

}
