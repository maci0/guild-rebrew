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
 * Byte-match note: RELOC, 1361/1361.  The
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
 * reference.
 *
 * Phase 2 uses TWO bases, matching the reference: the head reads (through
 * ptr2+0x21) stay on `q = ptr2 - 8`, and everything from the second
 * 10x8 loop onward moves to `b = ptr2 - 0x48`, which the reference holds
 * in ebp for the rest of the record (`lea edi,[ebp+0xb4]`,
 * `lea eax,[ebp+0x104]`, `add ebp,0x2ec` for the final version-gated
 * read).  Anchoring that tail on `q` instead cost 25 matches and 19 bytes.
 *
 * Every phase-2 read from the second 10x8 loop onward used to sit 0x10 too
 * high (b+0xc4 where the reference reads b+0xb4, through b+0x2fc against
 * b+0x2ec).  That was a real read-offset bug, not just a byte mismatch: the
 * reference's record layout is contiguous, the first 10x8 loop ending at
 * b+0xb4 exactly where the second begins (`lea edi,[ebp+0xb4]` at
 * 0x10013dfb, `add ebp,0x2ec` at 0x10014025).  Corrected, 727 -> 729.
 *
 * What closed the remaining edi<->ebx role swap (729 -> RELOC): `inner` and
 * `i` were function-scope locals shared by the phase-1 and phase-2 loops.
 * That shared residency pinned phase 2's record base into ebx instead of the
 * reference's edi, shifting every instruction from 174 on.  Declaring a
 * separate `inner`/`i` pair inside each of the two loop bodies freed the
 * register and the tail fell out with the reference's roles: 729 -> 1290.
 * The seven phase-2 sub-loops then needed the reference's statement order,
 * counter zeroed before the pointer is set up and incremented before the
 * pointer advances, which the `do { } while (i < N)` form emits: 1290 ->
 * 1357.  The last four bytes were the first 10x8 loop's latch, fixed by
 * moving its `inner += 8` into the `for` third clause so the increment pairs
 * with the counter: 1357 -> 1361/1361, RELOC.
 *
 * All 46 `~~` operands resolved: the only call target is 0x10012440
 * (ls_ReadVfsDataChecked, db/server.dll_functions.csv) and the only global
 * is 0x1002d4ec (g_file_version, rebrew_globals.h:18). */

int __cdecl ls_LoadTownData(int file)
{
	int count;
	int ptr;
	int ptr2;
	void* ctx;

	ctx = (void*) file;
	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, ctx)) {
			return 0;
		}
	}

	for (ptr = 0x1009b768; ptr < 0x100a8c38; ptr += 0x2a90) {
		char* inner;
		int i;
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
		char* b = (char*) (ptr2 - 0x48);
		char* inner;
		int i;

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
		for (i = 0; i < 10; i++, inner += 8) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
		}

		i = 0;
		inner = b + 0xb4;
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		if (!ls_ReadVfsDataChecked(b + 0x104, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x105, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x108;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		i = 0;
		inner = b + 0x118;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		if (!ls_ReadVfsDataChecked(b + 0x128, 4, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x12c;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 0xb);

		if (!ls_ReadVfsDataChecked(b + 0x137, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x138;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 7);

		if (!ls_ReadVfsDataChecked(b + 0x13f, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x140, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x141, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x142, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x144;
		do {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 0x12;
		} while (i < 8);

		if (!ls_ReadVfsDataChecked(b + 0x1d4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1d8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1dc, 0xd0, 1, ctx)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(b + 0x2ec, 8, 1, ctx)) {
				return 0;
			}
		}

		ptr2 += 0x2f4;
	}

	return 1;
}
