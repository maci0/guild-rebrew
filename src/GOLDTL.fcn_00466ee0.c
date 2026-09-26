typedef struct
{
	int i[0x3cc / 4];
} fcn_00466ee0_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466ee0_Ent;
// SIZE 0x2f4

#include "client_types.h"
typedef Tex_102d278 fcn_00466ee0_Tex;
// SIZE 0x160

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Tex_102d278 g_102d278[];
extern char s_67d420[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_00466cb0(int x, int y, int a3, int a4);
void __cdecl fcn_0046f650(int slot, fcn_00466ee0_Win* parent);

// FUNCTION: GOLDTL 0x466ee0
// SIZE: 249
int __cdecl fcn_00466ee0(int x, int y, int a3, int a4, int win)
{
	fcn_00466ee0_Win* w;
	int id;

	w = &((fcn_00466ee0_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		fcn_0041d9e0(s_67d420);
		return -1;
	}
	id = fcn_00466cb0(w->i[0x4 / 4] + x, w->i[0x8 / 4] - w->i[0x258 / 4] + y, a3, a4);
	fcn_0046f650(id, w);
	((fcn_00466ee0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
	((fcn_00466ee0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_00466ee0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x50 / 4];
	g_102d278[((fcn_00466ee0_Ent*)g_1015ea0)[id].i[0x88 / 4]].i[0] = w->i[0x28c / 4];
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = id;
	w->i[0x2c / 4]++;
	if (y > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = y + 4;
	}
	return id;
}
