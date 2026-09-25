#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_0046fdf0_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046fdf0_Ent;
// SIZE 0x2f4

extern fcn_0046fdf0_Win g_1015f40[];
extern fcn_0046fdf0_Ent* g_1015ea0;
extern int g_1015ea4;
extern int g_1040490;
extern int g_1040494;
extern int g_67d398;
extern char s_67d420[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_00469890(void);
int __cdecl fcn_0046b520(char* s, int font);
void __cdecl fcn_0046f650(int slot, fcn_0046fdf0_Win* parent);

// FUNCTION: GOLDTL 0x46fdf0
// SIZE: 411
int __cdecl fcn_0046fdf0(int x, int y, char* text, int win)
{
	fcn_0046fdf0_Win* w;
	int id;

	w = &g_1015f40[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		fcn_0041d9e0(s_67d420);
		return -1;
	}
	id = fcn_00469890();
	strcpy((char*) &g_1015ea0[id].i[0x90 / 4], text);
	if (w->i[0x28c / 4] != 0) {
		g_1015ea0[id].i[0x84 / 4] = w->i[0x28c / 4];
	} else {
		g_1015ea0[id].i[0x84 / 4] = g_67d398;
	}
	g_1015ea0[id].i[0x20 / 4] = 0x46;
	g_1015ea0[id].i[0x10 / 4] = w->i[0x4 / 4] + x;
	g_1015ea0[id].i[0x14 / 4] = w->i[0x8 / 4] - w->i[0x258 / 4] + y;
	g_1015ea0[id].i[0x18 / 4] = fcn_0046b520(text, g_1015ea0[id].i[0x84 / 4]) + 0x60;
	g_1015ea0[id].i[0x1c / 4] = g_1015ea4;
	g_1015ea0[id].i[0x24 / 4] = 2;
	g_1015ea0[id].i[0x40 / 4] = (int) w;
	g_1015ea0[id].i[0xc / 4] = (int) w;
	g_1015ea0[id].i[0x30 / 4] = 0;
	g_1015ea0[id].i[0x34 / 4] = g_1040490;
	g_1015ea0[id].i[0x28 / 4] = 0;
	g_1015ea0[id].i[0x2c / 4] = g_1040494;
	g_1015ea0[id].i[0x50 / 4] = g_1015ea0[w->i[0x27c / 4]].i[0x50 / 4];
	fcn_0046f650(id, w);
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = id;
	w->i[0x2c / 4]++;
	return id;
}
