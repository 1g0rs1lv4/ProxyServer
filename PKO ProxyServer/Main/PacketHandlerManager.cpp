#include <algorithm>
#include "PacketHandlerManager.h"

namespace PKO
{
	// �����������
	CPacketHandlerManager::CPacketHandlerManager()
	{
		// ����������� ������ ��� �����������
		m_handlers.reserve(16);
	}

	// ����������
	CPacketHandlerManager::~CPacketHandlerManager()
	{
		// ������� �����������
		handler_list_t::iterator it = m_handlers.begin();
		while (it != m_handlers.end())
		{
			delete *it;
			it++;
		}

		// ������ ������
		m_handlers.clear();
	}

	// �������� ����������
	void CPacketHandlerManager::attach(IPacketHandler *pHandler)
	{
		// ���������, ��� ����������� � ����� ID ��� � ������
		if (has(pHandler->getId())) {
			throw packet_handler_mgr_exception("Packet handler with ID " + std::to_string(pHandler->getId()) + " already exists in the storage!");
		}

		// ��������� ���������� � ������
		m_handlers.push_back(pHandler);
	}

	// ������� ����������
	void CPacketHandlerManager::detach(unsigned short int id)
	{
		// ���� ����������
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		// ���������� �� ������
		if (it == m_handlers.end()) {
			throw packet_handler_mgr_exception("No packet handler with ID " + std::to_string(id) + " in the storage!");
		}

		// ������� ����������
		delete *it;
		m_handlers.erase(it);
	}

	// �������� ����������
	IPacketHandler *CPacketHandlerManager::get(unsigned short int id) const
	{
		// ���� ����������
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		// ���������� �� ������
		if (it == m_handlers.end()) {
			throw packet_handler_mgr_exception("Undefined packet with ID " + std::to_string(id) + "!");
		}

		return *it;
	}

	// ��������� ����������
	bool CPacketHandlerManager::has(unsigned short int id) const
	{
		// ���� ����������
		auto it = std::find_if(m_handlers.begin(), m_handlers.end(), [&id](IPacketHandler *Handler)
			{
				return Handler->getId() == id;
			}
		);

		return (it != m_handlers.end());
	}
}