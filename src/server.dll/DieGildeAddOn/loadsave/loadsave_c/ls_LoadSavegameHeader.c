/* ls_LoadSavegameHeader — reads the versioned savegame header from a VFS
 * stream into the caller's buffer.
 *
 * Byte-identical (RELOC 857/857).  Two shapes decide it, and earlier rounds
 * could only ever reach one at a time:
 *
 * 1. `dest += 0x9c` inside each tail arm, rather than a hoisted `tail` local.
 *    This reproduces the reference's duplicated `add edi,0x9c` at 0x10012782
 *    and 0x100127a5 and its `cmp dword ptr [g_file_version],0x10039` memory
 *    compare.  On its own it swapped esi and edi across all 25 call sites
 *    (801/857): keeping `dest` live to the last instruction lost the tie.
 *
 * 2. The else arm written as one struct assignment from the global at
 *    0x1002d4f0 instead of three separate field stores.  Same emitted bytes
 *    (`mov edx,[g]; add edi,0x9c; mov [edi],edx; ...`, verified in
 *    .scratch/l2c/sc2.c), but it names `dest` once instead of three times,
 *    which drops dest's reference weight far enough to give edi to `dest`
 *    and esi to `stream` as the reference does.
 *
 * `#pragma pack(1)` on the struct is required: the natural layout pads the
 * trailing char to 12 bytes and costs 2 bytes (855/857).
 */

// FUNCTION: SERVER 0x10012470

#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern char s_ls_tmp_1002d4fc; /* 0x1002d4fc */

#include "../save_header_tail.h"
// SIZE 0x9
extern struct SaveHeaderTail g_save_header_tail; /* 0x1002d4f0 */

int __cdecl ls_LoadSavegameHeader(int stream, char* dest)
{
	void* buf;
	int i;

	buf = m_AllocTracked(0xe100, &s_ls_tmp_1002d4fc);
	if (!ls_ReadVfsDataChecked(dest, 4, 1, (void*) stream)) {
		return 0;
	}
	g_file_version = *(int*) dest;
	if (!ls_ReadVfsDataChecked(dest + 4, 1, 1, (void*) stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 5, 0x20, 1, (void*) stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 0x28, 8, 1, (void*) stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 0x30, 1, 1, (void*) stream)) {
		return 0;
	}
	if (g_file_version >= 0x10033) {
		if (!ls_ReadVfsDataChecked(dest + 0x31, 1, 1, (void*) stream)) {
			return 0;
		}
	}
	if (g_file_version >= 0x10028) {
		if (!ls_ReadVfsDataChecked(dest + 0x32, 0xe, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x40, 0x10, 1, (void*) stream)) {
			return 0;
		}
		if (g_file_version >= 0x10054) {
			if (!ls_ReadVfsDataChecked(dest + 0x50, 0x10, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x63, 1, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x64, 4, 1, (void*) stream)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(dest + 0x60, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x61, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x62, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x68, 4, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x6c, 1, 1, (void*) stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x6d, 1, 1, (void*) stream)) {
			return 0;
		}
		if (g_file_version >= 0x1002b) {
			if (!ls_ReadVfsDataChecked(dest + 0x70, 4, 1, (void*) stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x74, 4, 1, (void*) stream)) {
				return 0;
			}
		}
		else {
			*(int*) (dest + 0x70) = -1;
			*(int*) (dest + 0x74) = -1;
		}
		if (g_file_version >= 0x10034) {
			for (i = 0; i < 8; i++) {
				if (!ls_ReadVfsDataChecked(dest + 0x78 + i * 4, 4, 1, (void*) stream)) {
					return 0;
				}
			}
		}
		if (!ls_ReadVfsDataChecked(buf, 0xe100, 1, (void*) stream)) {
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
		if (!ls_ReadVfsDataChecked(dest + 0x98, 4, 1, (void*) stream)) {
			return 0;
		}
	}
	else {
		*(int*) (dest + 0x98) = 2;
	}
	if (g_file_version >= 0x10039) {
		dest += 0x9c;
		if (!ls_ReadVfsDataChecked(dest, 0x60, 1, (void*) stream)) {
			return 0;
		}
	}
	else {
		*(struct SaveHeaderTail*) (dest + 0x9c) = g_save_header_tail;
	}
	return 1;
}
