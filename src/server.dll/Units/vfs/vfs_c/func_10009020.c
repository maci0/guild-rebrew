#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int* __cdecl vfs_GetErrnoPtr(void);
int __cdecl vfs_WriteBufferLocked(void*, int, int, int);
void __cdecl m_FreeHeapLocked(void*);
int __cdecl vfs_FreeGameSubobject(void*);
int __cdecl vfs_CleanupSubobject(void*);
int __cdecl vfs_CompressBlock(void*, int);
int __cdecl vfs_LockedFwrite(void*, int, int, void*);
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl vfs_WriteUint32LE(int, unsigned int);
int __cdecl vfs_CloseStream(void*);
void __cdecl vfs_EntityCleanup(char*);

void __cdecl vfs_StreamClose(int);
int __cdecl vfs_Crc32Update(int checksum, int buffer, unsigned int size);
void __cdecl vfs_FreeSubobj(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);

int __cdecl ReadVfsCompressed(int, int, unsigned int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// STUB: SERVER 0x10009020
// OpenVfsStream

/* Game function - compression stream initialization */
/* Parses flag string (R/W/N/Z), allocates pool object, sets up zlib inflate/deflate */

int __cdecl OpenVfsStream(unsigned char* param_1, unsigned int param_2, char* param_3)
{
	char is_read;
	char use_zlib;
	char has_mode;
	char* obj;

	use_zlib = 1;
	has_mode = 1;
	is_read = 1;

	if (param_1 == 0) {
		return 0;
	}

	if (param_2 == 0) {
		return 0;
	}

	{
		char* p;
		char c;

		p = param_3;
		c = *p;
		while (c != 0) {
			int ch;
			ch = toupper(*p);

			switch (ch) {
			case 'N':
				use_zlib = 0;
				has_mode = 0;
				break;
			case 'R':
				is_read = 1;
				break;
			case 'W':
				is_read = 0;
				break;
			case 'Z':
				use_zlib = 1;
				has_mode = 0;
				break;
			}

			p++;
			c = *p;
		}
	}

	obj = m_PoolAlloc((char*) 0x10034670, 0x140, 0x10);
	{
		unsigned char flags;
		flags = *(unsigned char*) (obj + 0x13c);
		flags = (flags & 0xeb) | 0x22;
		*(unsigned char*) (obj + 0x13c) = flags;
	}

	if (is_read) {
		if (has_mode) {
			if (param_2 > 0xa && (unsigned int) param_1[0] == *(unsigned int*) 0x10029450 &&
				(unsigned int) param_1[1] == *(unsigned int*) 0x10029454) {
				use_zlib = 1;
				goto setup_inflate;
			}
			use_zlib = 0;
		}
		else {
			if (use_zlib) {
				goto setup_inflate;
			}
		}

		*(int*) (obj + 0x100) = (int) param_1;
		*(int*) (obj + 0x104) = (int) param_2;
		*(int*) (obj + 0x108) = 0;
		goto done;

	setup_inflate:
		*(int*) (obj + 0x100) = (int) (param_1 + 10);
		*(int*) (obj + 0x104) = (int) param_2 - 10;
		*(int*) (obj + 0x10c) = 0;
		*(int*) (obj + 0x110) = 0;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		{
			int ret;
			ret = inflateInit2_((z_stream*) (obj + 0x100), -15, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				goto done;
			}
			goto fail;
		}
	}
	else {
		if (!use_zlib) {
			*(int*) (obj + 0x10c) = (int) param_1;
			*(int*) (obj + 0x110) = (int) param_2;
			*(int*) (obj + 0x114) = 0;
			goto done;
		}

		if (param_2 <= 0x11) {
			goto fail;
		}

		param_1[0] = *(unsigned char*) 0x10029450;
		param_1[1] = *(unsigned char*) 0x10029454;
		param_1[2] = 8;
		param_1[8] = 0;
		param_1[7] = 0;
		param_1[6] = 0;
		param_1[5] = 0;
		param_1[4] = 0;
		param_1[3] = 0;
		param_1[9] = 0xb;

		*(int*) (obj + 0x100) = 0;
		*(int*) (obj + 0x104) = 0;
		*(int*) (obj + 0x10c) = (int) (param_1 + 10);
		*(int*) (obj + 0x110) = (int) param_2 - 10;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		*(int*) (obj + 0x138) = vfs_Crc32Update(0, 0, 0);

		{
			volatile int ret;
			ret = deflateInit2_((z_stream*) (obj + 0x100), -1, 8, -15, 8, 0, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				*(int*) (obj + 0x114) = 10;
				goto done;
			}
		}
	}

fail:
	m_PoolFree((char*) 0x10034670, obj);
	return 0;

done:
	if (obj != 0) {
		unsigned char flag_byte;

		*(int*) 0x10034678 = *(int*) 0x10034678 + 1;
		flag_byte = *(unsigned char*) (obj + 0x13c);
		flag_byte = (flag_byte & 0xf6) ^ (is_read & 1);
		flag_byte |= (use_zlib & 1) << 3;
		*(unsigned char*) (obj + 0x13c) = flag_byte;

		sprintf((char*) obj, (char*) 0x100294a4, param_1, param_2, is_read & 0xff, use_zlib & 0xff);
	}

	return (int) obj;
}
