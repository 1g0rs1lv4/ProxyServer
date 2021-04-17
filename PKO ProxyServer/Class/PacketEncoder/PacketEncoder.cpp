#include "PacketEncoder.h"
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

static char const basis_64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

namespace PKO
{

	bool inline __declspec(naked) rol_byte_off(byte* pb, unsigned int offset, byte bits)
	{
		__asm {
			push ebx
			push ecx
			push esi
			mov ecx, [esp + 24]; bits
			cmp cl, 8
			jl L1
			xor eax, eax
			jmp EXIT

			L1 :
			mov ebx, [esp + 16]; pb
				mov esi, [esp + 20]; offset
				mov al, byte ptr[ebx + esi]; *(pb + offset)
				rol al, cl
				mov byte ptr[ebx + esi], al
				mov eax, 1

				EXIT:
			pop esi
				pop ecx
				pop ebx
				ret
		}
	}

	bool inline __declspec(naked) ror_byte_off(byte* pb, unsigned int offset, byte bits)
	{
		__asm {
			push ebx
			push ecx
			push esi
			mov ecx, [esp + 24]; bits
			cmp cl, 8
			jl L1
			xor eax, eax
			jmp EXIT

			L1 :
			mov ebx, [esp + 16]; pb
				mov esi, [esp + 20]; offset
				mov al, byte ptr[ebx + esi]; *(pb + offset)
				ror al, cl
				mov byte ptr[ebx + esi], al
				mov eax, 1

				EXIT:
			pop esi
				pop ecx
				pop ebx
				ret
		}
	}

	bool inline __declspec(naked) xor_byte_off(byte* pb, unsigned int offset, byte mask)
	{ // xor a byte from a pb and a offset
		__asm {
			push ebx
			push ecx
			push esi
			mov ebx, [esp + 16]; pb
			mov esi, [esp + 20]; offset
			mov al, byte ptr[ebx + esi]; *(pb + offset)
			mov ecx, [esp + 24]; mask
			xor al, cl
			mov byte ptr[ebx + esi], al
			pop esi
			pop ecx
			pop ebx
			mov eax, 1
			ret
		}
	}

	int CPacketEncoder::base64(char const* src, unsigned int src_len, char* dst,
		unsigned int dst_max_len, unsigned int* dst_len)
	{
		unsigned char const* in = (unsigned char const*)src;
		unsigned char* out = (unsigned char*)dst;
		unsigned char oval;
		unsigned int olen;
		char* blah;

		olen = (src_len + 2) / 3 * 4;
		if (dst_len != NULL) *dst_len = olen;
		if (dst_max_len < olen) return -2;

		blah = (char*)out;
		while (src_len >= 3)
		{
			*out++ = basis_64[in[0] >> 2];
			*out++ = basis_64[((in[0] << 4) & 0x30) | (in[1] >> 4)];
			*out++ = basis_64[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
			*out++ = basis_64[in[2] & 0x3f];
			in += 3;
			src_len -= 3;
		}

		if (src_len > 0)
		{
			*out++ = basis_64[in[0] >> 2];
			oval = (in[0] << 4) & 0x30;
			if (src_len > 1) oval |= in[1] >> 4;
			*out++ = basis_64[oval];
			*out++ = (src_len < 2) ? '=' : basis_64[(in[1] << 2) & 0x3c];
			*out++ = '=';
		}

		if (olen < dst_max_len) *out = '\0';
		return true;
	}

	bool CPacketEncoder::encrypt_B(char* src, unsigned int src_len, char* key,
               unsigned int key_len, bool en /* = true */)
    { // 'B' encrypt/decrypt algorithm
	unsigned int loop = src_len / key_len;
    unsigned int rcnt = src_len % key_len;
    char* p = NULL;
    unsigned int i, j;
	//printf("CPacketEncoder::encrypt_B(data, %i, NULL, %i, %i) loop = %i | rcnt = %i\n", src_len, key_len, en, loop, rcnt);

    if (en)
	{
        p = src;
        for (j = 0; j < loop; ++ j)
            for (i = 0; i < key_len; ++ i)
			{
                xor_byte_off((byte *)p, j * key_len + i, key[i]);
                rol_byte_off((byte *)p, j * key_len + i, key[i] % key_len + 1);
			}
            for (i = 0; i < rcnt; ++ i)
			{
                xor_byte_off((byte *)p, loop * key_len + i, key[i]);
                rol_byte_off((byte *)p, loop * key_len + i, key[i] % key_len + 1);
			}
	}
    else
	{
        p = src;
        for (j = 0; j < loop; ++ j)
            for (i = 0; i < key_len; ++ i)
			{
                ror_byte_off((byte *)p, j * key_len + i, key[i] % key_len + 1);
                xor_byte_off((byte *)p, j * key_len + i, key[i]);
			}
            for (i = 0; i < rcnt; ++ i)
			{
                ror_byte_off((byte *)p, loop * key_len + i, key[i] % key_len + 1);
                xor_byte_off((byte *)p, loop * key_len + i, key[i]);
			}
	}
	//printf("printf encrypt_B END");
    return true;
	}

	void CPacketEncoder::init_Noise(int nNoise, char szKey[4])
	{
		szKey[0] = (char)(nNoise & 0x01);
		szKey[1] = (char)(nNoise & 0x02);
		szKey[2] = (char)(nNoise & 0x04);
		szKey[3] = (char)(nNoise & 0x08);
	}

	bool CPacketEncoder::encrypt_Noise(char szKey[4], char* src, unsigned int src_len)
	{
		//printf("encrypt_Noise src_len = %i\n", src_len);
		int nLen = src_len >> 2;
		if (nLen > 8)
		{
			nLen = 8;
		}
		int nCount = 0;
		for (int i = 0; i < nLen; i++)
		{
			src[nCount++] ^= szKey[3];
			src[nCount++] ^= szKey[2];
			src[nCount++] ^= szKey[1];
			src[nCount++] ^= szKey[0];
		}

		if (src_len >= 8)
		{
			szKey[0] = src[7] ^ (src[3] ^ 1);
			szKey[1] = src[6] ^ (src[2] ^ 2);
			szKey[2] = src[5] ^ (src[1] ^ 3);
			szKey[3] = src[4] ^ (src[0] ^ 4);
		}

		return true;
	}

	bool CPacketEncoder::decrypt_Noise(char szKey[4], char* src, unsigned int src_len)
	{
		//printf("decrypt_Noise src_len = %i\n", src_len);
		char szTemp[4];
		if (src_len >= 8)
		{
			szTemp[0] = src[7] ^ (src[3] ^ 1);
			szTemp[1] = src[6] ^ (src[2] ^ 2);
			szTemp[2] = src[5] ^ (src[1] ^ 3);
			szTemp[3] = src[4] ^ (src[0] ^ 4);
		}

		int nLen = src_len >> 2;
		if (nLen > 8)
		{
			nLen = 8;
		}
		int nCount = 0;
		for (int i = 0; i < nLen; i++)
		{
			src[nCount++] ^= szKey[3];
			src[nCount++] ^= szKey[2];
			src[nCount++] ^= szKey[1];
			src[nCount++] ^= szKey[0];
		}

		if (src_len >= 8)
		{
			szKey[0] = szTemp[0];
			szKey[1] = szTemp[1];
			szKey[2] = szTemp[2];
			szKey[3] = szTemp[3];
		}

		return true;
	}
}