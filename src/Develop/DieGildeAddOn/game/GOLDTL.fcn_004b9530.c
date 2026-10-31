

#include <string.h>

typedef struct Cmd {
	int handle;
	unsigned short text;
} Cmd;

typedef struct Ent {
	unsigned short id;
	short pad2;
	int handle;
} Ent;

typedef struct Obj {
	char pad0[0xac];
	int home;
	int work;
	int shop;
} Obj;

typedef struct Player {
	char name[0x2f4];
} Player;
// SIZE 0x2f4

extern unsigned char g_773d75;
extern char g_868060[];

Ent* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(Ent*, int);
Obj* __cdecl fcn_005463a0(int a, int b, int c);
Obj* __cdecl he_fn_Handlung(void);

int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl gm_RandomMod(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

int __cdecl fcn_004b9530(Cmd* cmd)
{
	char* shop;
	char* work;
	char* house;
	float f;
	Obj* objs[8];
	char* houses[8];
	char text[0x200];
	Ent* e;
	Obj* o;
	int amount;
	int n;
	int k;

	n = 0;
	e = gm_LookupEntityRecordById(cmd->handle);
	if (e == 0) {
		return 1;
	}
	if (fcn_005c6270(e, 0x290) != 0) {
		return 0x400;
	}
	for (o = fcn_005463a0(1, 0, 0xf); o != 0; o = he_fn_Handlung()) {
		if (n >= 8) {
			break;
		}
		gm_ResolveEntityById(0, (void**) (&house), 0, o->home);
		if (house != 0 && *(int*) (house + 0xa) == e->id) {
			gm_ResolveEntityById((void**) (&work), 0, 0, o->shop);
			gm_ResolveEntityById((void**) (&shop), 0, 0, o->work);
			if ((work != 0 && gm_CheckEntityType(work) != 0) || (shop != 0 && gm_CheckEntityType(shop) != 0)) {
				if ((shop != 0 && work != 0 && *shop == 'G') || *work == 'G') {
					objs[n] = o;
					houses[n] = house;
					n++;
				}
			}
		}
	}
	if (n == 0) {
		return 0x400;
	}
	f = ((gm_RandomMod(2) & 0xffff) + 1.0f) * 0.01f;
	amount = (int)(gm_WalkEntityChain(e->id) * f);
	fcn_004c51a0(-1, cmd->handle, g_773d75, amount);
	k = gm_RandomMod(n) & 0xffff;
	o = objs[k];
	house = houses[k];
	gm_ResolveEntityById((void**) (&shop), 0, 0, o->work);
	gm_ResolveEntityById((void**) (&work), 0, 0, o->shop);
	if (shop != 0 && work != 0) {
		if (*shop == 'G') {
			io_FormatTextBuffer(text, cmd->text + 0x12e7, ((Player*)g_868060)[0].name);
		} else {
			io_FormatTextBuffer(text, cmd->text + 0x12e7, ((Player*)g_868060)[*(int*) (work + 0x65)].name, amount);
		}
		fcn_00545d40(e->handle, e->handle, text, 0x100 < strlen(text), 0x5ef, 0);
	}
	return 0;
}
