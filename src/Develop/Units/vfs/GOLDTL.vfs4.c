#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>
#include "../../DieGildeAddOn/game/entity.h"

void __cdecl free(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_FlushAndClose(int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: GOLDTL 0x430580
// SIZE: 296
// CloseVfsStream


extern char g_stream_pool[1]; /* 0x6b7fe4 */
#define g_stream_count (*(int*) 0x6b7fec)

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



char s_gzip_mode_rb[4] = { 'r', 'b', 0, 0 };
