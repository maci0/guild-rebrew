#include "Develop/DieGildeAddOn/game/spiel.h"



#pragma pack(push, 1)
// SIZE 0x29
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x22];
	unsigned short slot;
} Player;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x22f];
	unsigned char level;
	char pad231[0x1c];
} Office;

// SIZE 0x6
typedef struct {
	char pad0[2];
	int id;
} Site;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	char pad0[2];
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x21c - 8];
} Entity;

// SIZE 0x8
typedef struct {
	char pad0[4];
	int id;
} Handle;

extern unsigned char* lpGebaeudePROT;
extern char g_7f4ca0[];
extern unsigned char g_773d75;


int __cdecl fcn_004c51f0(int, int, int, int, char, int);
int __cdecl fcn_0050b750(int, char);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004f36f0(Player*);
int __cdecl fcn_004c6090(Player*, int, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
Handle* __cdecl fcn_004c4480(int);
int __cdecl gm_CheckEntityType(Player*);
Site* __cdecl fcn_005049a0(Player*);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
void __cdecl init_Betrieb(Player*);

void __cdecl fcn_00512d20(Player* p)
{
	Office* o;
	int h;
	Handle* q;
	Site* s;

	gm_GetBuildingTypeCategory(p->office);
	o = &((Office*)lpGebaeudePROT)[p->office];
	if (o->kind == 9) {
		fcn_004c51f0(p->id, -1, 0x136, 1, (*(char*)&g_773d75), 0);
		fcn_004c5150(((Entity*)g_7f4ca0)[p->slot].id, -1, (*(char*)&g_773d75), fcn_0050b750(0x1f4, (*(char*)&g_773d75)));
	} else if (o->kind != 4 && o->kind != 0x10 && o->kind != 0x13) {
		fcn_004c51f0(p->id, -1, 0x134, 1, (*(char*)&g_773d75), 0);
	}
	if (o->kind != 9) {
		if (o->kind == 4 || o->kind == 0x10 || o->kind == 0x13 || o->kind == 0x1d) {
			if (o->kind == 0x1d) {
				h = fcn_004f36f0(p);
			} else {
				if (((Entity*)g_7f4ca0)[p->slot].type != 6 && ((Entity*)g_7f4ca0)[p->slot].type != 7) {
					fcn_004c6090(p, 0, o->level, 0);
				}
				h = fcn_004c6090(p, 0, o->level, 0);
			}
		} else {
			h = fcn_004c6090(p, 0, o->level, 0);
		}
		while (fcn_004c4450(h) == 0) {
			fcn_00535960();
		}
		q = fcn_004c4480(h);
		if (gm_CheckEntityType(p) == 0) {
			s = fcn_005049a0(p);
			if (s != 0) {
				cm_RequestChrMoveToUniverse(q->id, p->id, s->id, "dummy_EINGANG");
			}
		} else {
			cm_RequestChrMoveToUniverse(q->id, p->id, -1, "dummy_EINGANG");
		}
	}
	init_Betrieb(p);
}
