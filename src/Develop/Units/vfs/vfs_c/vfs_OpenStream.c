// FUNCTION: SERVER 0x10009020
#include "../../Error/error.h"
#include "../../m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
#include <stdio.h>
#include "../../../DieGildeAddOn/game/entity.h"
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl crt_toupper(int current_char);
/* Opens a VFS stream over a caller buffer. Parses the mode flags
 * (N = none, R = read, W = write, Z = zlib) and initializes the
 * stream structure with the matching inflate/deflate setup.
 *
 * Byte-identical to the reference apart from relocations (code 667 bytes;
 * the COMDAT also carries the 5-entry jump table and the 13-byte case map,
 * 701 in all).  What the match depends on:
 *   - The flag loop reads `*path_cursor` directly, with no hoisted char
 *     local: that gives the reference's `cmp byte ptr [eax],0` entry test.
 *   - The auto-detect branch spells `mode18 = 0` twice (size too small, and
 *     header mismatch).  msvc6 cross-jumps the two arms into one block, and
 *     that is what lays the plain setup out inline after `cmp ebp,0xa; ja`,
 *     with the header compares out of line.  A single `else` arm, `&&`/`||`
 *     chains and goto-label spellings all put the compares inline.
 *   - The flag byte at +0x13c is written through a bitfield struct at the
 *     end: the `read`/`compressed` bitfield stores are what give the
 *     reference's `and al,0xf6; xor al,cl; or al,bl` and put mode14 in cl
 *     from the post-alloc test onward.  Hand-written mask expressions left
 *     mode14 in al, which pushed the header compares to ecx and cost a byte
 *     (`mov ecx,[addr]` against the 5-byte A1 form).
 *   - sprintf's last two arguments are mode14 then mode18 ("read",
 *     "compressed"); the reference reloads [esp+0x18] after the first push,
 *     which is the mode14 slot at that depth. */

extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_pool_free(void* pool, void* item);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);

/* DATA: SERVER 0x100294a4
 * Must sit in this TU: link order already places vfs_OpenStream.c.obj
 * immediately before zutil.c.obj, so a named array here lands right before
 * z_errmsg.  A raw address cast emitted nothing and left the slot empty.
 * Declared before use — MSVC6 C requires it. */
char s_0x_08X_length_100294a4[] = "0x%08X -> length: %u, read: %u compressed: %u";


/* The stream flag byte at +0x13c. */
// SIZE 0x1
typedef struct {
	unsigned char read : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char compressed : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} vfs_mode_bits;

int __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* path_cursor;
	int result;
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
	stream = (char*) m_PoolAlloc((void*) 0x10034670, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (*(unsigned char*) &mode14 != 0) {
		if (mode13 != 0) {
			if (size <= 10) {
				mode18 = 0;
			} else if (buf[0] == *(int*) 0x10029450 && buf[1] == *(int*) 0x10029454) {
				mode18 = 1;
				goto inflate_setup;
			} else {
				mode18 = 0;
			}
		} else if (mode18 != 0) {
			goto inflate_setup;
		}
		*(char**) (stream + 0x100) = (char*) buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	inflate_setup:
		*(char**) (stream + 0x100) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x104) = size - 10;
		*(int*) (stream + 0x10c) = 0;
		*(int*) (stream + 0x110) = 0;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		if (inflateInit2_((void*) (stream + 0x100), -0xf, (char*) 0x1002706c, 0x38) == 0) {
			goto finalize;
		}
		goto cleanup;
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) 0x10029450;
		buf[1] = *(unsigned char*) 0x10029454;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
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
		g_stream_count = g_stream_count + 1;
		((vfs_mode_bits*) (stream + 0x13c))->read = *(unsigned char*) &mode14;
		((vfs_mode_bits*) (stream + 0x13c))->compressed = mode18;
		sprintf(stream, s_0x_08X_length_100294a4, buf, size, (unsigned char) mode14, mode18);
	}
	result = (int) stream;
done:
	return result;
cleanup:
	m_pool_free((void*) 0x10034670, stream);
	return 0;
}

