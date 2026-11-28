/* Owned (both targets) by src/GOLDTL.fcn_004af2f0.c. */
#include "Develop/DieGildeAddOn/game/object_prototype.h"

extern char* lpObjektePROT;
extern char* lpObjektePROT;

/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char gm_ActiveTownIndex;

/* Callees of this translation unit; see src/GOLDTL.fcn_004af2f0.c, the
 * sibling in the same address family. */
void* __cdecl gm_GetGuildHall(int);
void* __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl hst_SplitFormatPrefix(char*, char*, int*, char**);
int __cdecl atoi(char*);
int __cdecl gm_AmountToUnits(int, unsigned char);
void __cdecl io_FormatTextBuffer(void*, int, ...);




/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x20c) and
 * addresses the 0x200 scratch buffer off ebp; section 13 of
 * archived docs/msvc6-c-shapes.md.
 *
 * The out-length of fcn_004ae080 lives in the dead a4 argument home
 * ([ebp+0x14]) while the frame keeps only three slots.  msvc6 only packs it
 * there when the local is declared in its own block after the block-fill
 * (declaring it with the other locals spends a fourth slot and compiles the
 * frame to 0x210); the same block shape is what keeps the caller's copy of
 * a4 in esi, so the tail adds the length in edx instead of reusing esi. */
#pragma optimize("y", off)
int __cdecl hst_HandleStadtkasse(int unused1, int unused2, int unused3, char* token_text, int text_out)
{
	char buf[0x200];
	char* p;
	int v = 0;
	int len;
	void* e;
	unsigned short k;

	e = gm_GetGuildHall(1);
	if (e == 0)
		return 0;
	e = fcn_00502cd0(*(int*) ((char*) e + 0x5d), 2, 6, 0, 0x115);
	if (e == 0)
		return 0;
	e = fcn_00502cd0(*(int*) ((char*) e + 0x14), 1, 5);
	while (e != 0) {
		k = *(unsigned short*) e;
		if (((OBJECT_PROTOTYPE *)(*(int*)&lpObjektePROT))[k].kind == 9) {
			v = *(int*) ((char*) e + 0xe);
			break;
		}
		e = gm_NextEntityQueryMatch();
	}
	len = 0x200;
	p = buf;
	/* The original's zero-fill is the 24-byte hand-written block-fill prelude
	 * (archived docs/msvc6-c-shapes.md section 11, archived docs/codegen-walls.md section 6b);
	 * recorded C probes did not emit it.  Reproduced as a block-fill with ordinary
	 * named operands. */
	__asm {
		mov edi, p
		mov ebx, len
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
	{
		int n;

		hst_SplitFormatPrefix(token_text, buf, &n, &p);
		n = atoi(token_text + n);
		io_FormatTextBuffer((void*) text_out, (int) buf,
		    gm_AmountToUnits((int) (((float) n * 0.01f) * (float) v),
		    gm_ActiveTownIndex),
		    gm_ActiveTownIndex);
	}
	return 1;
}
