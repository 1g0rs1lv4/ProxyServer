#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "IPacketHandler.h"


namespace PKO
{

	// Определим тип для хранилища
	typedef std::vector<IPacketHandler *> handler_list_t;

	// Исключение для хранилища обработчиков
	class packet_handler_mgr_exception : public std::runtime_error
	{
		public:
			packet_handler_mgr_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~packet_handler_mgr_exception() { }
	};

	// Хранилище обработчиков пакетов
	class CPacketHandlerManager
	{
		public:
			
			// Конструктор
			CPacketHandlerManager();

			// Деструктор
			~CPacketHandlerManager();

			// Добавить обработчик
			void attach(IPacketHandler *pHandler);

			// Удалить обработчик
			void detach(unsigned short int id);

			// Получить обработчик
			IPacketHandler *get(unsigned short int id) const;

			// Проверить обработчик
			bool has(unsigned short int id) const;

		private:

			// Запретим копирование
			CPacketHandlerManager(const CPacketHandlerManager&) = delete;
			CPacketHandlerManager& operator=(const CPacketHandlerManager&) = delete;

			// Хранилище обработчиков
			handler_list_t m_handlers;
	};


}