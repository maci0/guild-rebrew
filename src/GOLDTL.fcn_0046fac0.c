#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_0046fac0_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046fac0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern int g_67d398;
extern char g_67d5bc[];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00469890(void);
int __cdecl m_alloc(int size, char* tag);
int __cdecl fcn_0046b520(char* s, int font);
char* __cdecl fcn_00466190(int id);
void __cdecl fcn_0046f650(int slot, fcn_0046fac0_Win* parent);

/* ADDRESS: GOLDTL 0x0046fac0 */
int __cdecl fcn_0046fac0(int x, int y, char* text, int win)
{
	fcn_0046fac0_Win* w;
	int id;

	w = &((fcn_0046fac0_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	if (w->i[0x2c / 4] >= 0x180) {
		fcn_0041d9e0(s_67d420);
		return -1;
	}
	id = fcn_00469890();
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x88 / 4] = m_alloc(0x101, g_67d5bc);
	if (((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x88 / 4] == 0) {
		return -1;
	}
	strcpy((char*) ((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x88 / 4], text);
	if (w->i[0x28c / 4] != 0) {
		((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x84 / 4] = w->i[0x28c / 4];
	} else {
		((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x84 / 4] = g_67d398;
	}
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x20 / 4] = 0x43;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x10 / 4] = w->i[0x4 / 4] + x;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x14 / 4] = w->i[0x8 / 4] - w->i[0x258 / 4] + y;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x18 / 4] = fcn_0046b520(text, ((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x84 / 4]) + 0x60;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x1c / 4] = *(unsigned short*) (fcn_00466190(((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x84 / 4]) + 8);
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x24 / 4] = 2;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0xc / 4] = (int) w;
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x30 / 4] = w->i[0x8 / 4];
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x34 / 4] = w->i[0x10 / 4] + w->i[0x8 / 4];
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x28 / 4] = w->i[0x4 / 4];
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x2c / 4] = w->i[0xc / 4] + w->i[0x4 / 4];
	((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_0046fac0_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x50 / 4];
	if (((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x1c / 4] + y > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = ((fcn_0046fac0_Ent*)g_1015ea0)[id].i[0x1c / 4] + y;
	}
	fcn_0046f650(id, w);
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = id;
	w->i[0x2c / 4]++;
	return id;
}
