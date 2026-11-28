

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

#include "Develop/DieGildeAddOn/game/entity_record.h"

Rec21c* __cdecl gm_LookupEntityRecordById(int);
void __cdecl hst_SplitFormatPrefix(char*, char*, int*, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl atoi(char*);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl hst_IsCandidateUnlisted(int);
unsigned short __cdecl gm_RandomMod(int);

int __cdecl gm_IsSlotActivePerson(unsigned short a1);
int __cdecl gm_IsSlotNpcPerson(int a1);
int __cdecl gm_IsSlotPlayerPerson(int a1);

#pragma optimize("y", off)
int __cdecl hst_HandleRndReich(int mode, int* pairs, int idx, char* text, void* out)
{
	char buf[0x200];
	int score[5];
	int found;
	unsigned short ids[5];
	int n;
	int sel;
	int i;
	int k;
	int v;
	int t;
	unsigned short w;
	Rec21c* r;
	int (__cdecl* test)(int);

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
	/* The fill pointer and the parse position live in separate blocks, so
	 * they share the reference's [ebp-0x10] slot; at function scope the asm
	 * operand lists weight the address-taken position above ids. */
	{
		int dst;

		n = 0x200;
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

		hst_SplitFormatPrefix(text, buf, &p, &rest);
		if (rest != 1 || (sel = atoi(text + p)) < 0 || sel > 2) {
			sel = 1;
		}
		if (sel == 0) {
			test = (int (__cdecl*)(int)) gm_IsSlotActivePerson;
		} else if (sel == 1) {
			test = gm_IsSlotNpcPerson;
		} else {
			test = gm_IsSlotPlayerPerson;
		}
	}
	if (mode == 1) {
		r = gm_LookupEntityRecordById(pairs[idx * 2 + 1]);
		if (r == 0 || r->active <= 0) {
			return 0;
		}
		goto send;
	}
	for (i = 0; i < 768; i++) {
		if (test(i) != 0) {
			v = gm_WalkEntityChain((unsigned short) i);
			if (v > score[4] && hst_IsCandidateUnlisted((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id)) != 0) {
				score[4] = v;
				found |= 1;
				ids[4] = (*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index);
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
	r = (Rec21c*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[ids[(unsigned short) gm_RandomMod(5)]];
	if (mode == 0) {
		pairs[idx * 2 + 1] = r->key;
	}
send:
	io_FormatTextBuffer(out, (int) buf, r->id);
	return 1;
}
#pragma optimize("", on)
