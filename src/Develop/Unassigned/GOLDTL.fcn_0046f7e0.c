#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046f7e0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00469c30(int x, int y, int a3);
void __cdecl fcn_0046f650(int slot, D2_WIN* parent);
void __cdecl fcn_00472680(int id, int a2);

/* ADDRESS: GOLDTL 0x0046f7e0 */
int __cdecl fcn_0046f7e0(int x, int y, int a3, int win, int a5)
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
	w->children[w->count] = fcn_00469c30((short) (w->left + x), (short) (w->top - (*(int*) &w->pad3c[0x21c]) + y), a3);
	id = w->children[w->count];
	if (id != -1) {
		fcn_0046f650(id, w);
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].parent) = (int) w;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_top) = 0;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_bottom) = d2_ScreenHeight;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_left) = 0;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_right) = g_1040494;
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_050) = (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[w->slot].value_050);
		(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_048) = (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[w->slot].value_048);
		fcn_00472680(id, a5);
		w->count++;
		if ((*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].height) + y > (*(int*) &w->pad3c[0x218])) {
			(*(int*) &w->pad3c[0x218]) = (*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].height) + y;
		}
	}
	return id;
}
