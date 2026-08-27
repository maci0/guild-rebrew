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
 * Byte-match note (2026-08-26/27): compiled 1354/1361 bytes, 758/1361 masked
 * matches (55.7%); prologue + phase 1 (0x0-0x1df) byte-identical.  The
 * count-read is MSVC6-split: `&count` lands in the dead file-arg slot
 * (lea [esp+0x18]) while the phase-1 loop bound reloads the 0x3e copy at
 * [esp+0x10] — the read value is dead, exactly as in the reference build.
 * Phase 1 needs the derived-sub-pointer forms (`hdr = ptr - 8`,
 * `r = inner - 8`) so MSVC6 folds them back into single-base lea [ebx-8]/
 * [edi-8] addressing instead of normalizing extra induction bases; the
 * outer loop variable must be an `int` (signed `jl` bound compare).
 * Phase 2 needs a `while` loop (the `for` form miscompiles: stride 0x5e8
 * instead of 0x2f4, skipping records) with an `int` loop variable (signed
 * `jl` bound compare, as in the reference) and the reads anchored on the
 * derived `q = ptr2 - 8`; ptr2 then stays memory-resident (arg-slot
 * induction, `mov ebx,[esp+0x18]` reload at the head) matching the
 * reference.  The 7-byte gap + phase-2 register plan (reference keeps
 * `ebp = ptr2-0x48` as a long-lived base with `ebx` counters; this C
 * keeps `q` in `edi` with `ebp` counters) is an MSVC6 register-allocation
 * choice not steerable from C — ~15 formulations tried (base-relative
 * variants trigger induction-variable elimination / constant-folding,
 * declaration order and `register` hints are ignored).
 * Resolved via `rebrew prove`: semantically PROVEN (EAX, 15 state pairs). */

int __cdecl ls_LoadTownData(int file)
{
	int count;
	int ptr;
	int ptr2;
	char* inner;
	int i;
	void* ctx;

	ctx = (void*) file;
	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, ctx)) {
			return 0;
		}
	}

	for (ptr = 0x1009b768; ptr < 0x100a8c38; ptr += 0x2a90) {
		char* hdr = (char*) (ptr - 8);
		if (!ls_ReadVfsDataChecked(hdr, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 0xc, 4, 1, ctx)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = (char*) (ptr + 0x10);
			do {
				char* r = inner - 8;
				if (!ls_ReadVfsDataChecked(r, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 4, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 8, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0xc, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x20, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x24, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x30, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x34, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x38, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x3c, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x2c, 4, 1, ctx)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

	}

	ptr2 = 0x100a8c88;
	while (ptr2 < 0x100a9858) {
		char* q = (char*) (ptr2 - 8);

		if (!ls_ReadVfsDataChecked(q - 0x40, 0x20, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 8, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0xc, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x10, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x14, 2, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x18, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x20, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x21, 1, 1, ctx)) {
			return 0;
		}

		inner = (char*) (ptr2 + 0x1c);
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			inner += 8;
		}

		inner = q + 0x74;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			inner += 8;
		}

		if (!ls_ReadVfsDataChecked(q + 0xc4, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0xc5, 1, 1, ctx)) {
			return 0;
		}

		inner = q + 0xc8;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			inner += 4;
		}

		inner = q + 0xd8;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			inner += 4;
		}

		if (!ls_ReadVfsDataChecked(q + 0xe8, 4, 1, ctx)) {
			return 0;
		}

		inner = q + 0xec;
		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(q + 0xf7, 1, 1, ctx)) {
			return 0;
		}

		inner = q + 0xf8;
		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(q + 0xff, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x100, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x101, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x102, 1, 1, ctx)) {
			return 0;
		}

		inner = q + 0x104;
		for (i = 0; i < 8; i++) {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, ctx)) {
				return 0;
			}
			inner += 0x12;
		}

		if (!ls_ReadVfsDataChecked(q + 0x194, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x198, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x19c, 0xd0, 1, ctx)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(q + 0x2ac, 8, 1, ctx)) {
				return 0;
			}
		}

		ptr2 += 0x2f4;
	}

	return 1;
}
