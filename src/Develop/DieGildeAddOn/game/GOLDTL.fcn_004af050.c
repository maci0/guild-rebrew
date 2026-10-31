

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad0[2];
	int key;
	unsigned char active;
	unsigned char side;
	char pad1[0x15c];
	unsigned char kind;
	char pad2[2];
	unsigned char grade;
	char pad3[0xb2];
} Rec21c;

extern char g_7f4ca0[];

Rec21c* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004ae080(char*, char*, int*, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl fcn_0064eeec(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004ae0f0(int);

int __cdecl fcn_004ae130(unsigned short a1);

#pragma optimize("y", off)
/* ADDRESS: GOLD 0x4aef10 */
int __cdecl fcn_004af050(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	int best;
	int want;
	int n;
	int sel;
	int i;
	int v;
	Rec21c* r;

	best = -10000000;
	want = 0;
	n = 0x200;
	/* Block scope lets the fill pointer and the parse position share the
	 * reference's [ebp-8] slot (same shape as fcn_004af800). */
	{
		int dst;

		dst = (int) buf;
		__asm {
		mov edi, dst
		mov ebx, n
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
	}
	{
		int p;
		int rest;

		fcn_004ae080(text, buf, &p, &rest);
		if (rest != 1) {
			return 0;
		}
		sel = fcn_0064eeec(text + p);
	}
	if (sel < 0 || sel > 2) {
		return 0;
	}
	n = 1;
	if (sel == 0) {
		n = 0;
	} else {
		want = sel != 1;
	}
	if (mode == 2) {
		return 0;
	}
	r = 0;
	if (mode == 1) {
		r = gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	for (i = 0; i < 768; i++) {
		if (fcn_004ae130((unsigned short) i) != 0 && (n == 0 || ((Rec21c*)g_7f4ca0)[i].side == want)) {
			v = gm_WalkEntityChain((unsigned short) i);
			if (v > best && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[i].key) != 0) {
				best = v;
				r = &((Rec21c*)g_7f4ca0)[i];
			}
		}
	}
	if (r == 0) {
		return 0;
	}
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)
