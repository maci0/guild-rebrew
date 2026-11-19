#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00465eb0_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_0046f650(int slot, D2_WIN* parent);

/* ADDRESS: GOLDTL 0x00465eb0 */
int __cdecl fcn_00465eb0(int id, int win)
{
	D2_WIN* w;
	int bottom;

	if (win < 0 || win > 0x60) {
		return 0;
	}
	w = &((D2_WIN*)g_1015f40)[win];
	if (w->active == 0) {
		return 0;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return 0;
	}
	fcn_0046f650(id, w);
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) w;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_00465eb0_Ent*)g_1015ea0)[w->slot].i[0x50 / 4];
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x30 / 4] = w->top;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x34 / 4] = w->height + w->top;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x28 / 4] = w->left;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x2c / 4] = w->width + w->left;
	((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x48 / 4] = ((fcn_00465eb0_Ent*)g_1015ea0)[w->slot].i[0x48 / 4];
	bottom = ((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x1c / 4] + ((fcn_00465eb0_Ent*)g_1015ea0)[id].i[0x14 / 4] - w->top;
	if (bottom > (*(int*) &w->pad3c[0x218])) {
		(*(int*) &w->pad3c[0x218]) = bottom + 4;
	}
	w->children[w->count] = id;
	w->count++;
	return 1;
}
