#include "CActionHandler.h"
#include "../../Binary/BinaryReader.h"
#include "../../Class/Player/Player.h"

namespace PKO
{
	// Конструктор
	CActionHandler::CActionHandler() :
		m_cha_id(0), m_action_id(0), m_state(0),
		m_point_number(0), m_kitbag_size(0)
	{

	}

	// Деструктор
	CActionHandler::~CActionHandler()
	{

	}

	// Получить ID пакета
	unsigned short int CActionHandler::getId() const
	{
		return 508;
	}


	// Прочитать пакет
	void CActionHandler::read(CBinaryReader& Reader, CPlayer& Player)
	{
		m_cha_id = static_cast<unsigned int>(Reader.readUint32());
		Reader.seek(4, seek_cur);
		m_action_id = static_cast<unsigned int>(Reader.readByte());

		// Действие - передвижение
		if (m_action_id == 1)
		{
			// Читаем состояние
			m_state = Reader.readUint16();
			if (m_state != 0) {
				Reader.readUint16();
			}

			// Читаем координаты
			if (Reader.free() > 0)
			{
				// Количество байт структуры координат
				unsigned int n = Reader.readUint16();

				// Количество точек
				m_point_number = n / sizeof(SPoint);

				// Читаем точки
				for (unsigned int i = 0; i < m_point_number; i++)
				{
					m_Points[i].x = htonl(Reader.readUint32()) / 100;
					m_Points[i].y = htonl(Reader.readUint32()) / 100;
				}
			}

			return;
		}

		// Действие - синхронизация инвентаря
		if (m_action_id == 6)
		{
			// ReadChaKitbagPacket
			if (static_cast<uint8_t>(Reader.readByte()) == 0) {
				m_kitbag_size = static_cast<uint16_t>(Reader.readUint16());
			}

			while (true)
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
					m_kitbagCells[grid_id].grid = grid_id;
					m_kitbagCells[grid_id].item_id = item_id;
					Reader.seek(20, seek_cur);

					// Корабль
					if (item_id == Player.stall_server()->config().vessel_deed_id()) {
						Reader.seek(4, seek_cur);
					}
					
					if (static_cast<uint8_t>(Reader.readByte()) != 0) {
						Reader.seek(20, seek_cur);
					}
				}
			}
		}
	}

	// Обработать пакет
	bool CActionHandler::handle(CPlayer& Player)
	{
		// Действие - перемещение
		if (m_action_id == 1 && m_state == 1)
		{
			// Ищем персонажа
			if (Player.character().getId() == m_cha_id)
			{
				// Получаем координаты персонажа
				unsigned int index = m_point_number - 1;
				unsigned int x = m_Points[index].x;
				unsigned int y = m_Points[index].y;

				// Устанавливаем координаты
				Player.character().setPos(x, y);
			}
		}
		// Дейстие - синхронизация инвентаря
		else if (m_action_id == 6)
		{
			
			// Ищем персонажа
			if (Player.character().getId() == m_cha_id)
			{
				// Устанавливаем инвентарь
				if (m_kitbag_size > 0) {
					Player.character().setKitbagSize(m_kitbag_size);
				}

				for (unsigned int i = 0; i < Player.character().getKitbagSize(); i++)
				{
					if (m_kitbagCells[i].item_id == 0) {
						continue;
					}

					Player.character().kitbag()[i].item_id = m_kitbagCells[i].item_id;
				}
			}

		}

		return true;
	}

	// Сбросить обработчик
	void CActionHandler::reset()
	{
		m_cha_id = 0;
		m_action_id = 0;
		m_state = 0;
		m_point_number = 0;
		m_kitbag_size = 0;

		for (unsigned int i = 0; i < MAX_KITBAG_SIZE; i++)
		{
			m_kitbagCells[i].grid = 0;
			m_kitbagCells[i].item_id = 0;
		}

		for (unsigned int i = 0; i < sizeof(m_Points) / sizeof(m_Points[0]); i++)
		{
			m_Points[i].x = 0;
			m_Points[i].y = 0;
		}
	}

	// Действие после отправки пакета
	void CActionHandler::after_send(CPlayer& Player) {



	}

};