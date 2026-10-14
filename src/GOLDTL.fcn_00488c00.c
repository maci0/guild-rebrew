

// The second scan indexes g_7f4ca0[i] directly and decrements cnt inside each
// call arm; an entity pointer or a shared decrement moves the strength-reduced
// anchor field and reorders the tail.

#include <string.h>

typedef struct Aux0488c00 {
	char pad0[0x2c];
	int id;
} Aux0488c00;

typedef struct Ent0488c00 {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int seed;
	char pad8[0x81 - 8];
	char pad81[0x82 - 0x81];
	unsigned char b82;
	unsigned char b83;
	char pad84[0x165 - 0x84];
	char active;
	char pad166[0x16c - 0x166];
	char* owner;
	char pad170[0x17c - 0x170];
	char* job;
	int pad180;
	Aux0488c00* aux;
	char pad188[0x1b4 - 0x188];
	int flags;
	char pad1b8[0x1c8 - 0x1b8];
	int flags2;
	char pad1cc[0x21c - 0x1cc];
} Ent0488c00;
// SIZE 0x21c

#pragma pack(push, 2)
typedef struct Pos0488c00 {
	int a;
	int b;
	int c;
	short d;
} Pos0488c00;

typedef struct Msg0488c00 {
	int pad0;
	unsigned char type;
	char pad5[3];
	int seed;
	int id;
	char pad10[0x28 - 0x10];
	Pos0488c00 pos;
	unsigned char flag;
	char pad37[0x58 - 0x37];
	unsigned char mode;
	char pad59[3];
	int target;
	int from;
	char pad64[0xf8 - 0x64];
} Msg0488c00;
#pragma pack(pop)

typedef struct Unit0488c00 {
	char pad0[0x16c];
	char* info;
} Unit0488c00;

extern char g_7f4ca0[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
#pragma pack(push, 1)
typedef struct Race0488c00 {
	char kind;
	char pad1[0x24d - 1];
} Race0488c00;
#pragma pack(pop)

extern unsigned char* g_868050;

char* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl fcn_004c5530(Msg0488c00* m);

void __cdecl fcn_00488c00(Unit0488c00* u)
{
	Msg0488c00 m;
	Ent0488c00* e;
	char* res;
	int cnt;
	int i;
	Race0488c00* race;

	cnt = 2;
	for (i = 0; i < 768; i++) {
		if (((Ent0488c00*)g_7f4ca0)[i].id != 0xffff && ((Ent0488c00*)g_7f4ca0)[i].owner == u->info && ((Ent0488c00*)g_7f4ca0)[i].active
		    && ((Ent0488c00*)g_7f4ca0)[i].job != 0 && *((Ent0488c00*)g_7f4ca0)[i].job == 0x16) {
			cnt--;
		}
	}
	if (cnt <= 0) {
		return;
	}
	race = &((Race0488c00*)g_868050)[*(unsigned char*)u->info];
	if (race->kind == 4) {
		res = fcn_00502cd0(*(int*)(u->info + 0x5d), 2, 6, 0, 0x60);
	} else if (race->kind == 0x13) {
		res = fcn_00502cd0(*(int*)(u->info + 0x5d), 2, 6, 0, 0x145);
	} else {
		res = 0;
	}
	memset(&m, 0, sizeof(m));
	m.type = 0x16;
	m.seed = ((Ent0488c00*)g_7f4ca0)[*(unsigned short*)(u->info + 0x27)].seed;
	m.id = *(int*)(u->info + 1);
	m.pos = (*(Pos0488c00*)&g_7f4c00);
	m.flag = 1;
	if (res != 0) {
		m.from = *(int*)(res + 2);
	} else {
		m.from = -1;
	}
	i = 0;
	do {
		if (i >= 768) {
			return;
		}
		if (((Ent0488c00*)g_7f4ca0)[i].id != 0xffff && ((Ent0488c00*)g_7f4ca0)[i].owner == u->info && ((Ent0488c00*)g_7f4ca0)[i].active && (((Ent0488c00*)g_7f4ca0)[i].flags & 0x10)) {
			if (((Ent0488c00*)g_7f4ca0)[i].job != 0) {
				if (*((Ent0488c00*)g_7f4ca0)[i].job == 0x16) {
					((Ent0488c00*)g_7f4ca0)[i].flags &= ~0x10;
				}
			} else if (((Ent0488c00*)g_7f4ca0)[i].aux != 0 && ((Ent0488c00*)g_7f4ca0)[i].aux->id == *(int*)(((Ent0488c00*)g_7f4ca0)[i].owner + 1)) {
				if (((Ent0488c00*)g_7f4ca0)[i].b83 < ((Ent0488c00*)g_7f4ca0)[i].b82) {
					m.target = ((Ent0488c00*)g_7f4ca0)[i].seed;
					m.mode = 3;
					fcn_004c5530(&m);
					cnt--;
				} else {
					m.target = ((Ent0488c00*)g_7f4ca0)[i].seed;
					m.mode = 2;
					fcn_004c5530(&m);
					cnt--;
				}
				((Ent0488c00*)g_7f4ca0)[i].flags2 |= 4;
			}
		}
		i++;
	} while (cnt > 0);
}
