#pragma once
#include <string>
#include "../../Main/IPacket.h"


namespace PKO
{
	class CGMNoticePacket : public IPacket
	{
		public:

			CGMNoticePacket();

			~CGMNoticePacket();

			// Получить ID пакета
			virtual unsigned short int getId() const;

			// Записать пакет в буфер
			virtual void write(CBinaryWriter& Writer);

			// Установить сообщение
			void setMessage(const std::string& message);

		private:

			// Запретим копирование
			CGMNoticePacket(const CGMNoticePacket&) = delete;
			CGMNoticePacket& operator=(const CGMNoticePacket&) = delete;
			
			// Сообщение
			std::string m_message;
	
	};
}

