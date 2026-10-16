#include "Develop/Units/d3/d3_object.h"
#include "client_sound.h"


// Plague event ("Sensenmann") state step: plays the plague track, then walks
// the event state at +0x70 (0 = pick the next target building, 2 = act on
// it). The target search tries up to 256 slots of the 0x90e094 table,
// stepping by +0xbc modulo 256, for a building whose kind bit is in the
// 0x807c4110 / bit-32 mask.

#pragma pack(push, 1)
typedef struct Bld {
	unsigned char kind;
	int id;
	char pad5[0x22];
	unsigned short x27;
	char pad29[0x80];
} Bld;
// SIZE 0xa9

typedef struct Level {
	unsigned char kind;
	char pad1[0x24c];
} Level;
// SIZE 0x24d

// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)

extern struct pos14 g_7f4c00;
extern int g_7749ec;
extern unsigned char* g_90e094;
extern unsigned char* g_868050;

int __cdecl fcn_00558370(char* e);
void __cdecl fcn_00546190(char* e);
void __cdecl fcn_004e4eb0(void);
void __cdecl fcn_004e4e90(char* name);
void __cdecl fcn_00500bb0(char* t, int a, int b, int c);
int __cdecl fcn_005589d0(char* e);
void __cdecl fcn_005b2880(void);
int __cdecl fcn_00558680(char* e);
int __cdecl fcn_00558b70(char* e);

void __cdecl fcn_0051af00(char*, char*, ...);

void __cdecl EvtSensenmann(char* e)
{
	int n;
	char buf[0x200];
	int r;
	int idx;
	int lo;
	int hi;
	unsigned char k;
	Bld* p;
	Level* q;

	if (*(int*) (e + 0x70) == -2 || *(int*) (e + 0x70) == -1) {
		if (*(int*) (e + 0xc8) != 0) {
			d3_DestroyObject((D3_OBJECT*) (*(int*) (e + 0xc8)));
		}
		if (g_7749ec != 0) {
			fcn_004e4eb0();
		}
		g_7749ec = 0;
		fcn_00546190(e);
		return;
	}
	if (*(int*) (e + 0xc8) == 0 && fcn_00558370(e) == 0) {
		fcn_00546190(e);
		if (g_7749ec != 0) {
			fcn_004e4eb0();
		}
		g_7749ec = 0;
		return;
	}
	if (g_7749ec == 0) {
		fcn_004e4e90("cd2\\DerSeuchenzug.mp3");
		if (g_772d1c != 0) {
			g_7749ec = 1;
		}
	}
	*(struct pos14*) (e + 0x52) = g_7f4c00;
	switch (*(int*) (e + 0x70)) {
	case 0:
		r = fcn_00558680(e);
		if (r == 1) {
			*(int*) (e + 0x70) = 0;
			fcn_00500bb0(e + 0x52, 0, 2, 0);
			return;
		}
		if (r == 2) {
			*(int*) (e + 0xb0) = *(int*) (e + 0xb4);
			if (*(int*) (e + 0xc0) <= 0) {
				if (*(int*) (e + 0xc0) == 0) {
					*(int*) (e + 0xb4) = *(int*) (e + 0xac);
					if (fcn_00558b70(e)) {
						fcn_00500bb0(e + 0x52, 0, 0xf, 0);
						*(int*) (e + 0x70) = 2;
						*(int*) (e + 0xc0) = *(int*) (e + 0xc0) - 1;
						return;
					}
					fcn_00500bb0(e + 0x52, 0, 2, 0);
					*(int*) (e + 0x70) = -1;
					return;
				}
				*(int*) (e + 0x70) = -1;
				return;
			}
			n = 0x100;
			idx = *(int*) (e + 0xb8);
			do {
				p = (Bld*) (g_90e094 + idx * sizeof(Bld));
				lo = 0;
				q = (Level*) (g_868050 + p->kind * sizeof(Level));
				k = q->kind;
				hi = 0;
				if (k > 0x1f) {
					hi = 1 << (k - 0x20);
				} else {
					lo = 1 << k;
				}
				if (p->x27 != 0xffff && ((lo & 0x807c4110) || (hi & 1))) {
					break;
				}
				p = 0;
				n--;
				idx = (idx + *(int*) (e + 0xbc)) % 256;
			} while (n != 0);
			*(int*) (e + 0xb8) = (*(int*) (e + 0xbc) + idx) % 256;
			if (p == 0) {
				*(int*) (e + 0x70) = -1;
				return;
			}
			fcn_0051af00(buf, "EvtSensenmann: next target = %G", p);
			*(int*) (e + 0xb4) = p->id;
			*(int*) (e + 0xc0) = *(int*) (e + 0xc0) - 1;
			if (fcn_00558b70(e)) {
				fcn_00500bb0(e + 0x52, 0, 0xf, 0);
				*(int*) (e + 0x70) = 2;
				return;
			}
			fcn_00500bb0(e + 0x52, 0, 2, 0);
			*(int*) (e + 0x70) = -1;
			return;
		}
		fcn_00500bb0(e + 0x52, 0, 2, 0);
		*(int*) (e + 0x70) = -1;
		return;
	case 2:
		fcn_00500bb0(e + 0x52, 0, 2, 0);
		if (fcn_005589d0(e)) {
			*(int*) (e + 0x70) = 0;
			return;
		}
		fcn_005b2880();
		*(int*) (e + 0x70) = -1;
		return;
	}
}
