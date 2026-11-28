#include "Develop/DieGildeAddOn/game/spiel.h"



/* Callees of this translation unit; see src/GOLDTL.fcn_004af2f0.c, the
 * sibling in the same address family. */

void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CalculateGebaeudeValue(void*, int);
void __cdecl hst_SplitFormatPrefix(char*, char*, int*, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x204) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * archived docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
/* ADDRESS: GOLDDE 0x0049d4f0 */
int __cdecl hst_HandleBestesWirtshaus(int mode, int tbl, int idx, char* token_text, int text_out)
{
	char buf[0x200];
	int entity = 0;
	int bestScore = -1;
	void* e;

	if (mode == 2)
		return 0;
	if (mode == 1) {
		gm_ResolveEntityById((void**) (&entity), 0, 0, *(int*) ((char*) tbl + idx * 8 + 4));
		if (entity == 0)
			return 0;
	} else {
		int score;

		e = gm_StartFilteredEntitySearch(1, 5, 0x16);
		while (e != 0) {
			score = gm_CalculateGebaeudeValue(e, *(signed char*) ((char*) e + 0x5c));
			if (score > bestScore) {
				entity = (int) e;
				bestScore = score;
			}
			e = gm_FindNextFilteredEntity();
		}
		if (entity == 0)
			return 0;
		if (mode == 0)
			*(int*) ((char*) tbl + idx * 8 + 4) = *(int*) ((char*) entity + 1);
	}
	/* The original keeps the scratch buffer pointer and its length in the
	 * dead a2/a3 argument homes ([ebp+0xc], [ebp+0x10]) and passes their
	 * addresses to fcn_004ae080, which is why no extra frame slot is
	 * allocated here; with separate locals msvc6 spills them instead
	 * (object 0x208 frame instead of 0x204). */
	tbl = (int) buf;
	idx = 0x200;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (archived docs/msvc6-c-shapes.md section 11, archived docs/codegen-walls.md section 6b);
	 * recorded C probes did not emit it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, tbl
		mov ebx, idx
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	hst_SplitFormatPrefix(token_text, buf, &tbl, &idx);
	io_FormatTextBuffer((void*) text_out, (int) buf, entity);
	return 1;
}
