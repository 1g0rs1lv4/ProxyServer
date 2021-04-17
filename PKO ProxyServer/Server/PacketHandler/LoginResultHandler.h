#pragma once
#include "../../Main/IPacketHandler.h"

namespace PKO
{

	// Коды ошибок
	enum result_t
	{
		result_success = 0,
		result_wrong_version = 7,
		result_wrong_username = 1001,
		result_wrong_password = 1002,
		result_already_online = 1104,
	};


	// Обработчик пакета с результатом входа на сервер
	// S -> C
	class CLoginResultHandler : public IPacketHandler
	{
		public:

			// Конструктор
			CLoginResultHandler();

			// Деструктор
			~CLoginResultHandler();

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
			CLoginResultHandler(const CLoginResultHandler&) = delete;
			CLoginResultHandler& operator=(const CLoginResultHandler&) = delete;

			// Код результата
			unsigned short int m_result;

			// Включение ли шифрование пакетов
			bool m_comm_encryption;

			// Ключ шифрования
			char m_encryption_key[12];

			// Длина ключа шифрование
			size_t m_encryption_key_length;


	};
}

