#include <string.h>

#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046fdf0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00469890(void);
int __cdecl fcn_0046b520(char* s, int font);
void __cdecl fcn_0046f650(int slot, D2_WIN* parent);

/* ADDRESS: GOLDTL 0x0046fdf0 */
int __cdecl d2_AddWindowText(int x, int y, char* text, int win)
{
	D2_WIN* w;
	int id;

	w = &((D2_WIN*)g_1015f40)[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	id = fcn_00469890();
	strcpy((char*) &((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x90 / 4], text);
	if ((*(int*) &w->pad280[12]) != 0) {
		((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x84 / 4] = (*(int*) &w->pad280[12]);
	} else {
		((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x84 / 4] = d2_DefaultFont;
	}
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x20 / 4] = 0x46;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x10 / 4] = w->left + x;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x14 / 4] = w->top - (*(int*) &w->pad3c[0x21c]) + y;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x18 / 4] = fcn_0046b520(text, ((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x84 / 4]) + 0x60;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x1c / 4] = d2_FontHeight;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x24 / 4] = 2;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0xc / 4] = (int) w;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x30 / 4] = 0;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x34 / 4] = d2_ScreenHeight;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x28 / 4] = 0;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x2c / 4] = g_1040494;
	((fcn_0046fdf0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_0046fdf0_Ent*)g_1015ea0)[w->slot].i[0x50 / 4];
	fcn_0046f650(id, w);
	w->children[w->count] = id;
	w->count++;
	return id;
}
