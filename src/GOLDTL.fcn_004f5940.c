// FUNCTION: GOLD 0x004f37e0
// SIZE: 304
// FUNCTION: GOLDTL 0x004f5940
// SIZE: 304

#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char pad4[0x16 - 4];
	int target;
	short count;
	unsigned char kind;
	char pad1d[0x21 - 0x1d];
	int arg;
	int state;
	char pad29[0x2d - 0x29];
} Order;
#pragma pack()

// SIZE 0x8
#include "client_types.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int owner;
	char pad8[0x21c - 8];
} Obj;

extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];
extern unsigned short g_774970;
extern char g_7f4ca0[];

int __cdecl fcn_004f5810(int key);
char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004fa980(int arg, unsigned char kind);
void __cdecl fcn_005b2a00(Obj* o, char* p);

int __cdecl fcn_004f5940(int key, int force)
{
	int k;
	char* p;
	int i;

	k = fcn_004f5810(key);
	if (k == -1) {
		return 3;
	}
	if (((Order*)g_9a3800)[k].count > 0) {
		((Order*)g_9a3800)[k].count--;
	}
	if (((Order*)g_9a3800)[k].count != 0 && force == 0) {
		return 2;
	}
	if (((Order*)g_9a3800)[k].state != 1 && (force == 0 || ((Order*)g_9a3800)[k].state == 0)) {
		return 1;
	}
	p = fcn_00508e40(((Order*)g_9a3800)[k].target);
	fcn_004fa980(((Order*)g_9a3800)[k].arg, ((Order*)g_9a3800)[k].kind);
	for (i = 0; i < 2048; i++) {
		if (key == g_99f800[i].key) {
			if (g_774970 != 0xffff && g_99f800[i].owner == ((Obj*)g_7f4ca0)[g_774970].owner && p != 0 && force == 0) {
				fcn_005b2a00(&((Obj*)g_7f4ca0)[g_774970], p);
			}
			g_99f800[i].owner = -1;
			g_99f800[i].key = -1;
		}
	}
	((Order*)g_9a3800)[k].state = 0;
	((Order*)g_9a3800)[k].target = -1;
	((Order*)g_9a3800)[k].id = -1;
	return 0;
}
