#include "../vfs.h"
extern char g_6b7fe4[];
#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl crt_toupper(int current_char);
/* Opens a VFS stream over a caller buffer. Parses the mode flags
 * (N = none, R = read, W = write, Z = zlib) and initializes the
 * stream structure with the matching inflate/deflate setup.
 * The body follows the server/Gold copy in ../vfs.c; the TL client has no
 * null check on the pool allocation before the finalize stores. */

#ifndef REBREW_SERVER
#define vfs_OpenStreamCount g_6b7fec
#endif
extern int vfs_OpenStreamCount;
extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_pool_free(void* pool, void* item);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);

typedef struct {
	unsigned char read : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char compressed : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} vfs_mode_bits_tl;

void* __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* path_cursor;
	void* result;
	int mode14;
	unsigned char mode13;
	unsigned char mode18;

	result = 0;
	*(unsigned char*) &mode14 = 1;
	mode18 = 1;
	mode13 = 1;
	if (buf == 0 || size <= 0) {
		goto done;
	}
	for (path_cursor = mode_flags; *path_cursor != 0; path_cursor++) {
		switch (crt_toupper(*path_cursor)) {
		case 'N':
			mode18 = 0;
			mode13 = 0;
			break;
		case 'R':
			*(unsigned char*) &mode14 = 1;
			break;
		case 'W':
			*(unsigned char*) &mode14 = 0;
			break;
		case 'Z':
			mode18 = 1;
			mode13 = 0;
			break;
		default:
			break;
		}
	}
	stream = (char*) m_PoolAlloc(g_6b7fe4, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (*(unsigned char*) &mode14 != 0) {
		if (mode13 != 0) {
			if (size <= 10) {
				mode18 = 0;
			} else if (buf[0] == *(int*) 0x679e60 && buf[1] == *(int*) 0x679e64) {
				mode18 = 1;
				goto inflate_setup;
			} else {
				mode18 = 0;
			}
		} else if (mode18 != 0) {
			goto inflate_setup;
		}
		*(unsigned char**) (stream + 0x100) = buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	inflate_setup:
		*(unsigned char**) (stream + 0x100) = buf + 10;
		*(unsigned int*) (stream + 0x104) = size - 10;
		*(int*) (stream + 0x10c) = 0;
		*(int*) (stream + 0x110) = 0;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		if (inflateInit2_((void*) (stream + 0x100), -0xf, "1.1.3", 0x38) == 0) {
			goto finalize;
		}
		goto cleanup;
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) 0x679e60;
		buf[1] = *(unsigned char*) 0x679e64;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
		buf[9] = 0xb;
		*(unsigned char**) (stream + 0x100) = 0;
		*(unsigned int*) (stream + 0x104) = 0;
		*(unsigned char**) (stream + 0x10c) = buf + 10;
		*(unsigned int*) (stream + 0x110) = size - 10;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		*(int*) (stream + 0x138) = crc32(0, 0, 0);
		if (deflateInit2_((void*) (stream + 0x100), -1, 8, -0xf, 8, 0, "1.1.3", 0x38) != 0) {
			goto cleanup;
		}
		*(int*) (stream + 0x114) = 0xa;
	} else {
		*(unsigned char**) (stream + 0x10c) = buf;
		*(unsigned int*) (stream + 0x110) = size;
		*(int*) (stream + 0x114) = 0;
	}
finalize:
	vfs_OpenStreamCount = vfs_OpenStreamCount + 1;
	((vfs_mode_bits_tl*) (stream + 0x13c))->read = *(unsigned char*) &mode14;
	((vfs_mode_bits_tl*) (stream + 0x13c))->compressed = mode18;
	sprintf(stream, "0x%08X -> length: %u, read: %u compressed: %u", buf, size, (unsigned char) mode14, mode18);
	result = stream;
done:
	return result;
cleanup:
	m_pool_free(g_6b7fe4, stream);
	return 0;
}
