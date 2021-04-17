#include "EnterMapHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"
#include "../../Server/Packet/GMNoticePacket.h"

namespace PKO
{
	// Конструткор
	CEnterMapHandler::CEnterMapHandler() :
		m_cha_id(0), m_cha_name(""), m_map_name(""),
		m_pos_x(0), m_pos_y(0), m_kitbag_size(0), m_gm(0)
	{

	}

	// Деструткор
	CEnterMapHandler::~CEnterMapHandler()
	{


	}

	// Получить ID пакета
	unsigned short int CEnterMapHandler::getId() const
	{
		return 516;
	}

	// Прочитать пакет
	void CEnterMapHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		unsigned int n = 0;

		// Читаем название карты, ID персонажа
		//  и имя персонажа
		Reader.seek(6, seek_cur);
		m_map_name = Reader.readString();
		Reader.seek(5, seek_cur);
		m_cha_id = Reader.readUint32();
		Reader.seek(4, seek_cur);
		m_cha_name = Reader.readString();
		m_gm = Reader.readByte();

		// Пропускаем лишние байты до координат
		Reader.seek(5, seek_cur);
		n = Reader.readUint16(); Reader.seek(n, seek_cur);
		n = Reader.readUint16(); Reader.seek(n + 6, seek_cur);
		n = Reader.readUint16(); Reader.seek(n, seek_cur);
		n = Reader.readUint16(); Reader.seek(n, seek_cur);
		n = Reader.readUint16(); Reader.seek(n + 2, seek_cur);

		// Читаем координаты персонажа
		m_pos_x = Reader.readUint32() / 100;
		m_pos_y = Reader.readUint32() / 100;

		// Пакет SLook 
		Reader.seek(18, seek_cur);
		n = Reader.readUint16(); Reader.seek(n, seek_cur);

		int syn_type = Reader.readByte();
		Reader.seek(2, seek_cur);
		if (static_cast<uint8_t>(Reader.readByte()) == 1) {
			Reader.seek(14, seek_cur);
		}
		else
		{
			Reader.seek(2, seek_cur);
			for (int i = 0; i < 10; i++)
			{
				// ID
				if (Reader.readUint16() == 0) {
					continue;
				}

				if (syn_type == 1) {
					Reader.seek(5, seek_cur);
					continue;
				}
				else {
					Reader.seek(12, seek_cur);
				}

				if (static_cast<uint8_t>(Reader.readByte()) == 0) {
					continue;
				}

				Reader.seek(8, seek_cur);
				if (static_cast<uint8_t>(Reader.readByte()) != 0) {
					Reader.seek(20, seek_cur);
				}
			}
		}

		// Пакет ChaPK
		Reader.seek(1, seek_cur);

		// AppendLookPacket
		for (int i = 0; i < 4; i++)
		{
			if (Reader.readUint16() != 0) {
				Reader.seek(1, seek_cur);
			}
		}

		// ReadChaSkillBagPacket
		Reader.seek(3, seek_cur);
		uint16_t skill_n = Reader.readUint16();
		for (uint16_t i = 0; i < skill_n; i++)
		{
			Reader.seek(14, seek_cur);
			if (Reader.readUint16() != 0) {
				Reader.seek(6, seek_cur);
			}
		}

		// ReadChaSkillStatePacket
		Reader.seek(2 * static_cast<uint8_t>(Reader.readByte()), seek_cur);

		// ReadChaAttrPacket
		Reader.seek(1, seek_cur);
		Reader.seek(5 * static_cast<uint16_t>(Reader.readUint16()), seek_cur);

		// ReadChaKitbagPacket
		if (static_cast<uint8_t>(Reader.readByte()) == 0) {
			m_kitbag_size = static_cast<uint16_t>(Reader.readUint16());
		}

		while(true)
		{
			int16_t grid_id = Reader.readUint16();
			if (grid_id < 0) {
				break;
			}

			if (grid_id > MAX_KITBAG_SIZE) {
				break;
			}

			uint16_t item_id = Reader.readUint16();
			if (item_id > 0)
			{
				// Запоминаем ячейку
				m_kitbagGrids[grid_id].grid = grid_id;
				m_kitbagGrids[grid_id].item_id = item_id;

				Reader.seek(20, seek_cur);
				if (static_cast<uint8_t>(Reader.readByte()) != 0) {
					Reader.seek(20, seek_cur);
				}
			}
		}
	}

	// Обработать пакет
	bool CEnterMapHandler::handle(CPlayer& Player)
	{
		// Обновляем персонажа
		Player.character().setId(m_cha_id);
		Player.character().setName(m_cha_name);
		Player.character().setMap(m_map_name);
		Player.character().setPos(m_pos_x, m_pos_y);
		Player.character().setGm(m_gm);

		// Обновляем инвентарь персонажа
		Player.character().setKitbagSize(m_kitbag_size);
		Player.character().kitbag().clear();
		Player.character().stall().init();

		for (unsigned int i = 0; i < m_kitbag_size; i++)
		{
			Player.character().kitbag().push_back(m_kitbagGrids[i]);
		}

		return true;
	}

	// Сбросить обработчик
	void CEnterMapHandler::reset()
	{
		m_cha_id = 0;
		m_cha_name = "";
		m_map_name = "";
		m_pos_y = 0;
		m_pos_y = 0;
		m_kitbag_size = 0;
		m_gm = 0;

		for (unsigned int i = 0; i < MAX_KITBAG_SIZE; i++)
		{
			m_kitbagGrids[i].grid = 0;
			m_kitbagGrids[i].item_id = 0;
		}
	}

	// Действие после отправки пакета
	void CEnterMapHandler::after_send(CPlayer& Player) {



	}

}

