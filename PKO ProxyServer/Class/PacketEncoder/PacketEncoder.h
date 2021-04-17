#pragma once

namespace PKO
{
	// Статический класс для шифрования и расшифрования пакетов
	class CPacketEncoder
	{
	public:

		static void init_Noise(int nNoise, char szKey[4]);
		static bool encrypt_Noise(char szKey[4], char* src, unsigned int src_len);
		static bool decrypt_Noise(char szkey[4], char* src, unsigned int src_len);
		static int base64(char const* src, unsigned int src_len, char* dst, unsigned int dst_max_len, unsigned int* dst_len);
		static bool encrypt_B(char* src, unsigned int src_len, char* key, unsigned int key_len, bool en = true);
	};
}