#include <algorithm>
#include "PacketHandlerManager.h"

namespace PKO
{
	// Конструктор
	CPacketHandlerManager::CPacketHandlerManager()
	{
		// Резервируем память под обработчики
		m_handlers.reserve(16);
	}

	// Деструктор
	CPacketHandlerManager::~CPacketHandlerManager()
	{
		// Удаляем обработчики
		handler_list_t::iterator it = m_handlers.begin();
		while (it != m_handlers.end())
		{
			delete *it;
			it++;
		}

		// Чистим список
		m_handlers.clear();
	}

	// Добавить обработчик
	void CPacketHandlerManager::attach(IPacketHandler *pHandler)
	{
		// Проверяем, что обработчика с даным ID нет в списке
		if (has(pHandler->getId())) {
			throw packet_handler_mgr_exception("Packet handler with ID " + std::to_string(pHandler->getId()) + " already exists in the storage!");
		}

		// Добавляем обработчик в список
		m_handlers.push_back(pHandler);
	}

	// Удалить обработчик
	void CPacketHandlerManager::detach(unsigned short int id)
	{
		// Ищем обработчик
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		// Обработчик не найден
		if (it == m_handlers.end()) {
			throw packet_handler_mgr_exception("No packet handler with ID " + std::to_string(id) + " in the storage!");
		}

		// Удаляем обработчик
		delete *it;
		m_handlers.erase(it);
	}

	// Получить обработчик
	IPacketHandler *CPacketHandlerManager::get(unsigned short int id) const
	{
		// Ищем обработчик
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		// Обработчик не найден
		if (it == m_handlers.end()) {
			throw packet_handler_mgr_exception("Undefined packet with ID " + std::to_string(id) + "!");
		}

		return *it;
	}

	// Проверить обработчик
	bool CPacketHandlerManager::has(unsigned short int id) const
	{
		// Ищем обработчик
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		return (it != m_handlers.end());
	}
}