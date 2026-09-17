#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

void __cdecl free(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_FlushAndClose(int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: SERVER 0x10008C80
// vfs_CleanupObject

int __cdecl vfs_CleanupObject(char* obj)
{
	char* sub;
	int result;
	result = 0;
	if (!obj) {
		return -102;
	}
	sub = *(char**) (obj + 0x7c);
	if (!sub) {
		return -102;
	}
	if (!*(int*) (sub + 0x5c)) {
		if (*(int*) (sub + 0x50) != *(int*) (sub + 0x54)) {
			result = -105;
		}
	}
	if (*(int*) sub) {
		free(*(void**) sub);
	}
	*(int*) sub = 0;
	if (*(int*) (sub + 0x40)) {
		inflateEnd((void*) (sub + 4));
	}
	*(int*) (sub + 0x40) = 0;
	free(sub);
	*(int*) (obj + 0x7c) = 0;
	return result;
}

/* Closes a VFS stream with full cleanup. Handles both
 * compressed and plain streams, flushing and deallocating
 * zlib state if needed. */

// FUNCTION: SERVER 0x10008d10
// CloseVfsStream


extern int g_stream_count;
extern char g_stream_pool[1];

int __cdecl CloseVfsStream(void* stream)
{
	int result;
	int n;
	unsigned int value;
	char* write_cursor;

	result = 0;
	if (stream != 0) {
		if (*(unsigned char*) ((char*) stream + 0x13c) & 0x20) {
			if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
				if (*(unsigned char*) ((char*) stream + 0x13c) & 1) {
					inflateEnd((char*) stream + 0x100);
				} else {
					deflate((char*) stream + 0x100, 4);
					deflateEnd((char*) stream + 0x100);
					if (*(unsigned int*) ((char*) stream + 0x110) >= 8) {
						write_cursor = *(char**) ((char*) stream + 0x10c);
						value = *(unsigned int*) ((char*) stream + 0x138);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						value = *(unsigned int*) ((char*) stream + 0x108);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						*(unsigned int*) ((char*) stream + 0x114) += 8;
						*(char**) ((char*) stream + 0x10c) += 8;
						*(unsigned int*) ((char*) stream + 0x110) -= 8;
					}
				}
			}
			if (!(*(unsigned char*) ((char*) stream + 0x13c) & 1)) {
				result = *(unsigned int*) ((char*) stream + 0x114);
			}
		} else {
				if (*(void**) ((char*) stream + 0x100) != 0) {
					if ((*(unsigned char*) ((char*) stream + 0x13c) & 1) && (*(unsigned char*) ((char*) stream + 0x13c) & 0x10)) {
						vfs_CleanupObject(*(void**) ((char*) stream + 0x100));
						vfs_DestroyEntity(*(void**) ((char*) stream + 0x100));
					} else if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
						vfs_FlushAndClose((int) *(void**) ((char*) stream + 0x100));
					} else {
						fclose(*(void**) ((char*) stream + 0x100));
					}
				}
		}
		g_stream_count--;
		m_pool_free((int*) 0x10034670, stream);
	}
	return result;
}


/* DATA: SERVER 0x1002944c..0x100294a0
 *
 * The reference places "rb\\0\\0" (fopen mode), then the gzip magic dwords
 * 0x1f / 0x8b, then the vfs.c path and the gz-compressed-file message.
 * Without the 12-byte prefix, this TU's named strings start at 0x1002944c
 * and displace everything after them.  Callers already push/cmp the raw
 * addresses (gm_Open, vfs_OpenStream, vfs_ReadData); nothing names these
 * symbols, but they must occupy this exact span. */

char s_rb_1002944c[4] = { 'r', 'b', 0, 0 };
unsigned int g_gzip_magic_1f_10029450 = 0x1f;
unsigned int g_gzip_magic_8b_10029454 = 0x8b;
char s_D__Develop_Units_vfs_vfs_c_10029458[] = "D:\\Develop\\Units\\vfs\\vfs.c";
char s_vfs__gz_compressed_file____s___i_10029474[] = "vfs: gz-compressed file (\"%s\") in zip found!";

