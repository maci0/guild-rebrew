// FUNCTION: SERVER 0x10009020
#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl crt_toupper(int c);
/* Opens a VFS stream over a caller buffer. Parses the mode flags
 * (N = none, R = read, W = write, Z = zlib) and initializes the
 * stream structure with the matching inflate/deflate setup. */

// CFLAGS: /O2 /Gd

extern int g_10034678;
extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_PoolFree(void* pool, void* item);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);

int __cdecl OpenVfsStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* p;
	int idx;
	unsigned char mode13;
	unsigned char mode14;
	unsigned char mode18;

	mode14 = 1;
	mode18 = 1;
	mode13 = 1;
	if (buf == 0 || size <= 0) {
		return 0;
	}
	for (p = mode_flags; *p != 0; p++) {
		idx = crt_toupper(*p) - 0x4e;
		switch (idx) {
		case 0:
			mode18 = 0;
			mode13 = 0;
			break;
		case 4:
			mode14 = 1;
			break;
		case 9:
			mode14 = 0;
			break;
		case 12:
			mode18 = 1;
			mode13 = 0;
			break;
		default:
			break;
		}
	}
	stream = (char*) m_PoolAlloc((void*) 0x10034670, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (mode14 != 0) {
		if (mode13 != 0) {
			if (size > 10) {
				if (buf[0] == *(int*) 0x10029450 && buf[1] == *(int*) 0x10029454) {
					mode18 = 1;
					goto inflate_setup;
				}
			}
			mode18 = 0;
		}
		if (mode18 != 0) {
inflate_setup:
			*(char**) (stream + 0x100) = (char*) buf + 10;
			*(unsigned int*) (stream + 0x104) = size - 10;
			*(int*) (stream + 0x10c) = 0;
			*(int*) (stream + 0x110) = 0;
			*(int*) (stream + 0x120) = 0;
			*(int*) (stream + 0x124) = 0;
			if (inflateInit2_((void*) (stream + 0x100), -0xf, (char*) 0x1002706c, 0x38) != 0) {
				goto cleanup;
			}
			goto finalize;
		}
		*(char**) (stream + 0x100) = (char*) buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) 0x10029450;
		buf[1] = *(unsigned char*) 0x10029454;
		buf[2] = 8;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		buf[6] = 0;
		buf[7] = 0;
		buf[8] = 0;
		buf[9] = 0xb;
		*(char**) (stream + 0x100) = 0;
		*(unsigned int*) (stream + 0x104) = 0;
		*(char**) (stream + 0x10c) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x110) = size - 10;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		*(int*) (stream + 0x138) = crc32(0, 0, 0);
		if (deflateInit2_((void*) (stream + 0x100), -1, 8, -0xf, 8, 0, (char*) 0x1002706c, 0x38) != 0) {
			goto cleanup;
		}
		*(int*) (stream + 0x114) = 0xa;
	} else {
		*(char**) (stream + 0x10c) = (char*) buf;
		*(unsigned int*) (stream + 0x110) = size;
		*(int*) (stream + 0x114) = 0;
	}
finalize:
	if (stream != 0) {
		g_10034678++;
		*(unsigned char*) (stream + 0x13c) = (unsigned char) (((*(unsigned char*) (stream + 0x13c) & 0xf6) ^ (mode14 & 1)) | ((mode18 & 1) << 3));
		sprintf(stream, (char*) 0x100294a4, buf, size, mode18, mode18);
	}
	return (int) stream;
cleanup:
	m_PoolFree((void*) 0x10034670, stream);
	return 0;
}


