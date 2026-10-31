#include "Develop/DieGildeAddOn/game/spiel.h"



/* Callees of this translation unit; see src/GOLDTL.fcn_004af2f0.c, the
 * sibling in the same address family. */

void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_0050cf50(void*, int);
void __cdecl fcn_004ae080(char*, char*, int*, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x204) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md. */
#pragma optimize("y", off)
int __cdecl fcn_004af1d0(int a1, int a2, int a3, char* a4, int a5)
{
	char buf[0x200];
	int v = 0;
	int r = -1;
	void* e;

	if (a1 == 2)
		return 0;
	if (a1 == 1) {
		gm_ResolveEntityById((void**) (&v), 0, 0, *(int*) ((char*) a2 + a3 * 8 + 4));
		if (v == 0)
			return 0;
	} else {
		int s;

		e = gm_StartFilteredEntitySearch(1, 5, 0x16);
		while (e != 0) {
			s = fcn_0050cf50(e, *(signed char*) ((char*) e + 0x5c));
			if (s > r) {
				v = (int) e;
				r = s;
			}
			e = gm_FindNextFilteredEntity();
		}
		if (v == 0)
			return 0;
		if (a1 == 0)
			*(int*) ((char*) a2 + a3 * 8 + 4) = *(int*) ((char*) v + 1);
	}
	/* The original keeps the scratch buffer pointer and its length in the
	 * dead a2/a3 argument homes ([ebp+0xc], [ebp+0x10]) and passes their
	 * addresses to fcn_004ae080, which is why no extra frame slot is
	 * allocated here; with separate locals msvc6 spills them instead
	 * (object 0x208 frame instead of 0x204). */
	a2 = (int) buf;
	a3 = 0x200;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-c-shapes.md section 11, docs/codegen-walls.md section 6b);
	 * no msvc6 C spelling emits it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, a2
		mov ebx, a3
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
	fcn_004ae080(a4, buf, &a2, &a3);
	io_FormatTextBuffer((void*) a5, (int) buf, v);
	return 1;
}
