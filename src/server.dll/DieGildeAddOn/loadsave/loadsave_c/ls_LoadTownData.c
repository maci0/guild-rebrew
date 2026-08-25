// FUNCTION: SERVER 0x10013b10
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"
#include "../../../Units/vfs/vfs.h"
#include "../../game/entity.h"

#include <stdlib.h>

extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char _ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_file_version; /* 0x1002d4ec */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern int g_101de454; /* 0x101de454 */
extern int g_101de55c; /* 0x101de55c */
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* ls_LoadTownData — two-phase save load.  Phase 1 walks the per-player
 * building-slot table (0x1009b768, stride 0x2a90): 4 header dwords, then
 * `count` (default 0x3e) records of 0x80 bytes.  Phase 2 walks the town
 * records (0x100a8c88, stride 0x2f4) with name/timestamps/flags/population/
 * resource pairs/political state.
 *
 * Byte-match note: best proper C is 274/1361 (20%) — NEAR_MATCHING is not
 * reachable.  The reference build keeps the frame to ONE local (push ecx;
 * count only) with ptr/ebp/edi fully register-resident (ctx=esi, ptr=ebx,
 * i=ebp, inner=edi, then ptr2/base reusing edi/ebp), and the inner loop
 * emits per-read lea [edi-8]/[edi-4] without extra induction bases.  MSVC6
 * compiles every C formulation tried (10+ across pointer types, int/char*
 * ptr, for/do-while/while loops, struct-record reads, scope isolation,
 * split counters, /O1 /Ox /Os /Og- /G5 /Oy- flags) to a 2-local frame
 * (sub esp,8) with the inner loop strength-reduced into extra base
 * registers (inner-4/inner+4), spilling ptr and i.  See
 * docs/msvc6-allocator.md (base-normalization + register-cascade classes);
 * docs/TODO.md lists the same blocker with rebrew "register hints" as the
 * intended fix. */

int __cdecl ls_LoadTownData(int file)
{
	int count;
	char* ptr;
	char* ptr2;
	char* inner;
	char* base;
	int i;
	void* ctx;

	ctx = (void*) file;
	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, ctx)) {
			return 0;
		}
	}

	for (ptr = (char*) 0x1009b768; ptr < (char*) 0x100a8c38; ptr += 0x2a90) {
		if (!ls_ReadVfsDataChecked(ptr - 8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, ctx)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = ptr + 0x10;
			do {
				if (!ls_ReadVfsDataChecked(inner - 8, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner - 4, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 4, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x18, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x1c, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x28, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x2c, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x30, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x34, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x24, 4, 1, ctx)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

	}

	ptr2 = (char*) 0x100a8c88;
	do {
		base = ptr2 - 0x48;

		if (!ls_ReadVfsDataChecked(base, 0x20, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 - 8, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 0xc, 2, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 0x10, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 0x18, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr2 + 0x19, 1, 1, ctx)) {
			return 0;
		}

		inner = ptr2 + 0x1c;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			inner += 8;
		}

		inner = base + 0xb4;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			inner += 8;
		}

		if (!ls_ReadVfsDataChecked(base + 0x104, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x105, 1, 1, ctx)) {
			return 0;
		}

		inner = base + 0x108;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			inner += 4;
		}

		inner = base + 0x118;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			inner += 4;
		}

		if (!ls_ReadVfsDataChecked(base + 0x128, 4, 1, ctx)) {
			return 0;
		}

		inner = base + 0x12c;
		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x137, 1, 1, ctx)) {
			return 0;
		}

		inner = base + 0x138;
		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x13f, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x140, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x141, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x142, 1, 1, ctx)) {
			return 0;
		}

		inner = base + 0x144;
		for (i = 0; i < 8; i++) {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, ctx)) {
				return 0;
			}
			inner += 0x12;
		}

		if (!ls_ReadVfsDataChecked(base + 0x1d4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1d8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1dc, 0xd0, 1, ctx)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(base + 0x2ec, 8, 1, ctx)) {
				return 0;
			}
		}

		ptr2 += 0x2f4;
	} while (ptr2 < (char*) 0x100a9858);

	return 1;
}
