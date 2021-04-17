#pragma once
#include <string>
#include "../../Main/IPacket.h"


namespace PKO
{
	class CPopupNoticePacket : public IPacket
	{
		public:

			CPopupNoticePacket(const std::string& message);

			~CPopupNoticePacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);


		private:

			// Запретим копирование
			CPopupNoticePacket(const CPopupNoticePacket&) = delete;
			CPopupNoticePacket& operator=(const CPopupNoticePacket&) = delete;
			
			// Сообщение
			std::string m_message;
	
	};
}

