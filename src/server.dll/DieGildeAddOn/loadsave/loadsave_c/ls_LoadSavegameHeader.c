/* ls_LoadSavegameHeader — reads the versioned savegame header from a VFS
 * stream into the caller's buffer (g_save_info).
 *
 * Byte-match note: 801/857 bytes match; the 56 remaining diffs are a pure
 * MSVC 6.0 register cascade (docs/msvc6-allocator.md) — the reference keeps
 * `stream` in esi and `dest` in edi, this C compiles to the swap (stream in
 * edi, dest in esi).  Every structural probe compiles byte-identical apart
 * from the ModRM/push/pop register bytes.  The cascade is anchored on the
 * live load `g_file_version = *(int*) dest` between the first two reads
 * (removing that statement flips the allocation to the reference roles);
 * ~25 formulations of the load/store, parameter aliasing, and the tail
 * pointer advance (dest += 0x9c) were tried without steering the GRA. */

// FUNCTION: SERVER 0x10012470

#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern int g_1002d4f0; /* 0x1002d4f0 */
extern int g_1002d4f4; /* 0x1002d4f4 */
extern char g_1002d4f8; /* 0x1002d4f8 */
extern char g_1002d4fc; /* 0x1002d4fc */

int __cdecl ls_LoadSavegameHeader(int stream, char* dest)
{
	void* buf;
	int i;

	buf = m_AllocTracked(0xe100, &g_1002d4fc);
	if (!ReadVfsDataChecked(dest, 4, 1, (void*) stream)) {
		return 0;
	}
	g_file_version = *(int*) dest;
	if (!ReadVfsDataChecked(dest + 4, 1, 1, (void*) stream)) {
		return 0;
	}
	if (!ReadVfsDataChecked(dest + 5, 0x20, 1, (void*) stream)) {
		return 0;
	}
	if (!ReadVfsDataChecked(dest + 0x28, 8, 1, (void*) stream)) {
		return 0;
	}
	if (!ReadVfsDataChecked(dest + 0x30, 1, 1, (void*) stream)) {
		return 0;
	}
	if (g_file_version >= 0x10033) {
		if (!ReadVfsDataChecked(dest + 0x31, 1, 1, (void*) stream)) {
			return 0;
		}
	}
	if (g_file_version >= 0x10028) {
		if (!ReadVfsDataChecked(dest + 0x32, 0xe, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x40, 0x10, 1, (void*) stream)) {
			return 0;
		}
		if (g_file_version >= 0x10054) {
			if (!ReadVfsDataChecked(dest + 0x50, 0x10, 1, (void*) stream)) {
				return 0;
			}
			if (!ReadVfsDataChecked(dest + 0x63, 1, 1, (void*) stream)) {
				return 0;
			}
			if (!ReadVfsDataChecked(dest + 0x64, 4, 1, (void*) stream)) {
				return 0;
			}
		}
		if (!ReadVfsDataChecked(dest + 0x60, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x61, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x62, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x68, 4, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x6c, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ReadVfsDataChecked(dest + 0x6d, 1, 1, (void*) stream)) {
			return 0;
		}
		if (g_file_version >= 0x1002b) {
			if (!ReadVfsDataChecked(dest + 0x70, 4, 1, (void*) stream)) {
				return 0;
			}
			if (!ReadVfsDataChecked(dest + 0x74, 4, 1, (void*) stream)) {
				return 0;
			}
		}
		else {
			*(int*) (dest + 0x70) = -1;
			*(int*) (dest + 0x74) = -1;
		}
		if (g_file_version >= 0x10034) {
			for (i = 0; i < 8; i++) {
				if (!ReadVfsDataChecked(dest + 0x78 + i * 4, 4, 1, (void*) stream)) {
					return 0;
				}
			}
		}
		if (!ReadVfsDataChecked(buf, 0xe100, 1, (void*) stream)) {
			return 0;
		}
	}
	if (buf != 0) {
		m_FreeTracked(buf);
	}
	if (g_file_version < 0x10025) {
		return 0;
	}
	if (g_file_version >= 0x10038) {
		if (!ReadVfsDataChecked(dest + 0x98, 4, 1, (void*) stream)) {
			return 0;
		}
	}
	else {
		*(int*) (dest + 0x98) = 2;
	}
	if (g_file_version >= 0x10039) {
		dest += 0x9c;
		if (!ReadVfsDataChecked(dest, 0x60, 1, (void*) stream)) {
			return 0;
		}
	}
	else {
		dest += 0x9c;
		*(int*) dest = g_1002d4f0;
		*(int*) (dest + 4) = g_1002d4f4;
		*(char*) (dest + 8) = g_1002d4f8;
	}
	return 1;
}
