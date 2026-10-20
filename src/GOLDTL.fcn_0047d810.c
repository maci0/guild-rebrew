#include "client_actions.h"

#pragma pack(push, 1)
typedef struct Ent47d {
	unsigned short id;
	unsigned char kind;
	char pad3;
	unsigned int seed;
	char pad8[0x21c - 8];
} Ent47d;
// SIZE 0x21c

typedef struct Bld47d {
	unsigned char kind;
	char pad1[4];
	char name[0x22];
	unsigned short x27;
	char pad29[0x5a - 0x29];
	unsigned char x5a;
	char pad5b[0xa9 - 0x5b];
} Bld47d;
// SIZE 0xa9

typedef struct Level47d {
	unsigned char kind;
	char pad1[0x223 - 1];
	unsigned char x223;
	char pad224[0x230 - 0x224];
	unsigned char x230;
	char pad231[0x24d - 0x231];
} Level47d;
// SIZE 0x24d
#pragma pack(pop)

extern unsigned char* g_868050;
extern char g_7f4ca0[];

int __cdecl fcn_0047d240(Ent47d*);
Ent47d* __cdecl fcn_0047d2a0(Ent47d*);
void __cdecl fcn_004a3530(Ent47d*);
void __cdecl fcn_004c6090(Bld47d*, int, int, int);
int __cdecl fcn_00495180(int);
void __cdecl fcn_00495690(int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl sprintf(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0047d810 */
void __cdecl fcn_0047d810(Ent47d* e)
{
	int n;
	char buf[1024];
	int found;
	unsigned int lo;
	unsigned int hi;
	Bld47d* p;
	Level47d* q;
	char* r;
	unsigned int state;
	int x223;
	int x230;

	if (!fcn_0047d240(e)) {
		return;
	}
	if (*(unsigned int*) ((char*) e + 0x1cc) & 0x3000) {
		return;
	}
	n = 0x100;
	p = *(Bld47d**) 0x90e094;
	do {
		if (p->kind) {
			q = &((Level47d*) g_868050)[p->kind];
			lo = 0;
			hi = 0;
			if (q->kind > 0x1f) {
				hi = 1 << (q->kind - 0x20);
			}
			else {
				lo = 1 << q->kind;
			}
			if (p->x27 == e->id && !(p->x5a & 1)
			 && ((*(unsigned int*) 0x666028 & lo) || (*(unsigned int*) 0x66602c & hi))) {
				found = 0;
				r = (char*) 0x7f4ca2;
				do {
					if ((int) r >= 0x85a0a2) {
						break;
					}
					if (*(unsigned short*) (r - 2) != 0xffff
					 && *(Bld47d**) (r + 0x16a) == p
					 && (*(unsigned char*) r == 1 || *(unsigned char*) r == 2)) {
						found = 1;
					}
					r += 0x21c;
				} while (!found);
				if (gm_GetBuildingTypeCategory(p->kind) != 6 && !found) {
					q = &((Level47d*) g_868050)[p->kind];
					x223 = q->x223;
					x230 = q->x230;
					fcn_004c6090(p, 1, x230, x223);
					sprintf(buf, (char*) 0x67db58, *(unsigned short*) &g_7f4c04,
					 *(int*) 0x7f4c06, (char*) e + 0x30, p->name);
				}
			}
		}
		p++;
		n--;
	} while (n);
	if (*(unsigned char*) ((char*) e + 8) <= 0) {
		return;
	}
	*(int*) 0x77261c = (int) fcn_0047d2a0(e);
	fcn_004a3530(e);
	state = *((unsigned char*) e + 0x132);
	if (!*((char*) e + 0x1b1) && fcn_00495180(e->id)) {
		if (*((unsigned char*) e + 0x132) != state
		 || (*(unsigned int*) (0x10085d0 + *((unsigned char*) e + 0x132) * 0x94) & 0x200)) {
			fcn_00495690(e->id);
		}
	}
	*(int*) 0x77261c = 0;
}
