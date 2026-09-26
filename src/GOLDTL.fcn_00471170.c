#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_00471170_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00471170_Ent;
// SIZE 0x2f4

typedef struct
{
	int pad000;
	int wins[0x60];
	int count;
	char pad188[0x198 - 0x188];
	int ready;
	char pad19c[0x1a4 - 0x19c];
	int surf[2];
	int back[2];
	char pad1b4[0x2bc - 0x1b4];
} fcn_00471170_Page;
// SIZE 0x2bc

typedef struct
{
	int f00;
	int w;
	int h;
	char pad0c[0x28 - 0xc];
	int fmt;
	char pad2c[0x5c - 0x2c];
} fcn_00471170_Desc;
// SIZE 0x5c

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Obj_1038140 g_1038140[];
extern int g_14ce86c;

int __cdecl fcn_00470820(int a, int b, int c);
int __cdecl fcn_004770a0(fcn_00471170_Desc* d, int flags);

// FUNCTION: GOLDTL 0x471170
// SIZE: 341
int __cdecl fcn_00471170(int a, int b, int c)
{
	int id;
	int i;
	int j;
	fcn_00471170_Page* p;
	fcn_00471170_Win* w;
	fcn_00471170_Desc d;

	id = fcn_00470820(a, b, c);
	if (id != 0) {
		p = &((fcn_00471170_Page*)g_1038140)[id];
		for (i = 0; i < p->count; i++) {
			w = &((fcn_00471170_Win*)g_1015f40)[p->wins[i]];
			((fcn_00471170_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x48 / 4] = 1;
			for (j = 0; j < w->i[0x2c / 4]; j++) {
				((fcn_00471170_Ent*)g_1015ea0)[((int*) w->i[0x28 / 4])[j]].i[0x48 / 4] = 1;
			}
		}
		p->ready = 1;
		for (i = 0; i < 2; i++) {
			memset(&d, 0, sizeof(d));
			d.w = 0x100;
			d.h = 0x100;
			d.fmt = g_14ce86c;
			p->surf[i] = fcn_004770a0(&d, 0x10);
			memset(&d, 0, sizeof(d));
			d.w = 0x100;
			d.h = 0x100;
			d.fmt = g_14ce86c;
			p->back[i] = fcn_004770a0(&d, 0x10);
		}
		return id;
	}
	return 0;
}
