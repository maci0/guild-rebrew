#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466ee0_Ent;
// SIZE 0x2f4

#include "client_types.h"
typedef Tex_102d278 fcn_00466ee0_Tex;
// SIZE 0x160

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Tex_102d278 g_102d278[];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00466cb0(int x, int y, int a3, int a4);
void __cdecl fcn_0046f650(int slot, D2_WIN* parent);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00466ee0 */
int __cdecl fcn_00466ee0(int x, int y, int a3, int a4, int win)
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
	id = fcn_00466cb0(w->left + x, w->top - (*(int*) &w->pad3c[0x21c]) + y, a3, a4);
	fcn_0046f650(id, w);
	*(int*) (&((D2_CONTROL_TL*) g_1015ea0)[id].parent) = (int) w;
	((D2_CONTROL_TL*) g_1015ea0)[id].value_050 = ((D2_CONTROL_TL*) g_1015ea0)[w->slot].value_050;
	g_102d278[((D2_CONTROL_TL*) g_1015ea0)[id].value_088].i[0] = (*(int*) &w->pad280[12]);
	w->children[w->count] = id;
	w->count++;
	if (y > (*(int*) &w->pad3c[0x218])) {
		(*(int*) &w->pad3c[0x218]) = y + 4;
	}
	return id;
}
