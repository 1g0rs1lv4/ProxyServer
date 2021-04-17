#pragma once
#include <string>
#include "../../Main/IPacketHandler.h"

namespace PKO
{
	// Обработчик смены персональных данных
	// C -> S
	class СChangePasswordHandler : public IPacketHandler
	{
	public:

		// Конструктор
		СChangePasswordHandler();

		// Деструктор
		~СChangePasswordHandler();

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
		СChangePasswordHandler(const СChangePasswordHandler&) = delete;
		СChangePasswordHandler& operator=(const СChangePasswordHandler&) = delete;

		std::string szOld;
		std::string szPassword;
	};
}