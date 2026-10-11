// FUNCTION: GOLDTL 0x4afb60

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad0[2];
	int key;
	unsigned char active;
	unsigned char side;
	char pad1[0x15a];
	unsigned char cls;
	char pad1b;
	unsigned char kind;
	char pad2[2];
	unsigned char grade;
	char pad3[0xb2];
} Rec21c;

extern char g_7f4ca0[];

Rec21c* __cdecl fcn_00508e40(int);
void __cdecl fcn_004ae080(char*, char*, int*, int*);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_0064eeec(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004ae0f0(int);
unsigned short __cdecl gm_RandomMod(int);

int __cdecl fcn_004ae130(unsigned short a1);

#pragma optimize("y", off)
int __cdecl fcn_004afb60(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	int score[5];
	int found;
	unsigned short ids[5];
	int n;
	int i;
	int k;
	int v;
	int t;
	unsigned short w;
	Rec21c* r;

	score[0] = -10000000;
	score[1] = -10000000;
	score[2] = -10000000;
	score[3] = -10000000;
	score[4] = -10000000;
	found = 0;
	ids[0] = 0xffff;
	ids[1] = 0xffff;
	ids[2] = 0xffff;
	ids[3] = 0xffff;
	ids[4] = 0xffff;
	if (mode == 2) {
		return 0;
	}
	n = 0x200;
	/* Block scope lets the fill pointer and the parse position share one
	 * frame slot (same shape as fcn_004af800). */
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
	}
	if (mode == 1) {
		r = fcn_00508e40(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	for (i = 0; i < 768; i++) {
		if (((Rec21c*)g_7f4ca0)[i].cls >= 0x13 && ((Rec21c*)g_7f4ca0)[i].cls <= 0x45
		    && (((Rec21c*)g_7f4ca0)[i].cls < 0x1f || ((Rec21c*)g_7f4ca0)[i].cls > 0x21)
		    && (((Rec21c*)g_7f4ca0)[i].cls < 0x28 || ((Rec21c*)g_7f4ca0)[i].cls > 0x2d)
		    && (((Rec21c*)g_7f4ca0)[i].cls < 0x34 || ((Rec21c*)g_7f4ca0)[i].cls > 0x39)
		    && fcn_004ae130((unsigned short) i) != 0) {
			v = gm_WalkEntityChain((unsigned short) i);
			if (v > score[4] && fcn_004ae0f0(((Rec21c*)g_7f4ca0)[i].key) != 0) {
				score[4] = v;
				found |= 1;
				ids[4] = ((Rec21c*)g_7f4ca0)[i].id;
				for (k = 3; k >= 0; k--) {
					if (score[k + 1] > score[k]) {
						t = score[k];
						w = ids[k];
						score[k] = score[k + 1];
						score[k + 1] = t;
						ids[k] = ids[k + 1];
						ids[k + 1] = w;
					}
				}
			}
		}
	}
	if (found == 0) {
		return 0;
	}
	r = &((Rec21c*)g_7f4ca0)[ids[(unsigned short) gm_RandomMod(5)]];
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	fcn_0051af00(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)
