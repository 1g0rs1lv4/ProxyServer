#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "IPacketHandler.h"


namespace PKO
{

	// ��������� ��� ��� ���������
	typedef std::vector<IPacketHandler *> handler_list_t;

	// ���������� ��� ��������� ������������
	class packet_handler_mgr_exception : public std::runtime_error
	{
		public:
			packet_handler_mgr_exception(const std::string& what_arg) :
				std::runtime_error(what_arg) { }
			virtual ~packet_handler_mgr_exception() { }
	};

	// ��������� ������������ �������
	class CPacketHandlerManager
	{
		public:
			
			// �����������
			CPacketHandlerManager();

			// ����������
			~CPacketHandlerManager();

			// �������� ����������
			void attach(IPacketHandler *pHandler);

			// ������� ����������
			void detach(unsigned short int id);

			// �������� ����������
			IPacketHandler *get(unsigned short int id) const;

			// ��������� ����������
			bool has(unsigned short int id) const;

		private:

			// �������� �����������
			CPacketHandlerManager(const CPacketHandlerManager&) = delete;
			CPacketHandlerManager& operator=(const CPacketHandlerManager&) = delete;

			// ��������� ������������
			handler_list_t m_handlers;
	};


}