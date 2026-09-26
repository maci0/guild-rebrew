typedef struct
{
	int i[0x3cc / 4];
} fcn_0046f7e0_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046f7e0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern int g_1040490;
extern int g_1040494;
extern char s_67d420[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_00469c30(int x, int y, int a3);
void __cdecl fcn_0046f650(int slot, fcn_0046f7e0_Win* parent);
void __cdecl fcn_00472680(int id, int a2);

// FUNCTION: GOLDTL 0x46f7e0
// SIZE: 338
int __cdecl fcn_0046f7e0(int x, int y, int a3, int win, int a5)
{
	fcn_0046f7e0_Win* w;
	int id;

	w = &((fcn_0046f7e0_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		fcn_0041d9e0(s_67d420);
		return -1;
	}
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = fcn_00469c30((short) (w->i[0x4 / 4] + x), (short) (w->i[0x8 / 4] - w->i[0x258 / 4] + y), a3);
	id = ((int*) w->i[0x28 / 4])[w->i[0x2c / 4]];
	if (id != -1) {
		fcn_0046f650(id, w);
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x30 / 4] = 0;
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x34 / 4] = g_1040490;
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x28 / 4] = 0;
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x2c / 4] = g_1040494;
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_0046f7e0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x50 / 4];
		((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x48 / 4] = ((fcn_0046f7e0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x48 / 4];
		fcn_00472680(id, a5);
		w->i[0x2c / 4]++;
		if (((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x1c / 4] + y > w->i[0x254 / 4]) {
			w->i[0x254 / 4] = ((fcn_0046f7e0_Ent*)g_1015ea0)[id].i[0x1c / 4] + y;
		}
	}
	return id;
}
