// FUNCTION: GOLDTL 0x004b9530

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

Ent* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(Ent*, int);
Obj* __cdecl fcn_005463a0(int a, int b, int c);
Obj* __cdecl fcn_005462a0(void);
int __cdecl fcn_005015e0(char** dynamic, char** existing, char** static_ptr, int entity_id);
int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(unsigned short id);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(char*, int, ...);
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
	e = fcn_00508e40(cmd->handle);
	if (e == 0) {
		return 1;
	}
	if (fcn_005c6270(e, 0x290) != 0) {
		return 0x400;
	}
	for (o = fcn_005463a0(1, 0, 0xf); o != 0; o = fcn_005462a0()) {
		if (n >= 8) {
			break;
		}
		fcn_005015e0(0, &house, 0, o->home);
		if (house != 0 && *(int*) (house + 0xa) == e->id) {
			fcn_005015e0(&work, 0, 0, o->shop);
			fcn_005015e0(&shop, 0, 0, o->work);
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
	f = ((fcn_0042e410(2) & 0xffff) + 1.0f) * 0.01f;
	amount = fcn_0050dac0(e->id) * f;
	fcn_004c51a0(-1, cmd->handle, g_773d75, amount);
	k = fcn_0042e410(n) & 0xffff;
	o = objs[k];
	house = houses[k];
	fcn_005015e0(&shop, 0, 0, o->work);
	fcn_005015e0(&work, 0, 0, o->shop);
	if (shop != 0 && work != 0) {
		if (*shop == 'G') {
			fcn_0051af00(text, cmd->text + 0x12e7, ((Player*)g_868060)[0].name);
		} else {
			fcn_0051af00(text, cmd->text + 0x12e7, ((Player*)g_868060)[*(int*) (work + 0x65)].name, amount);
		}
		fcn_00545d40(e->handle, e->handle, text, 0x100 < strlen(text), 0x5ef, 0);
	}
	return 0;
}
