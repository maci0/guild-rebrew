#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00465eb0_Ent;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
void __cdecl d2_InsertControlAfterWindow(int slot, D2_WIN* parent);

/* ADDRESS: GOLDTL 0x00465eb0 */
/* ADDRESS: GOLDDE 0x00459ae0 */
int __cdecl d2_AddWindowChild(int id, int win)
{
	D2_WIN* w;
	int bottom;

	if (win < 0 || win > 0x60) {
		return 0;
	}
	w = &((D2_WIN*)d2_Windows)[win];
	if (w->active == 0) {
		return 0;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return 0;
	}
	d2_InsertControlAfterWindow(id, w);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].parent) = (int) w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_050) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->slot].value_050);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_top) = w->top;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_bottom) = w->height + w->top;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_left) = w->left;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_right) = w->width + w->left;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_048) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->slot].value_048);
	bottom = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) + (*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].y) - w->top;
	if (bottom > (*(int*) &w->pad3c[0x218])) {
		(*(int*) &w->pad3c[0x218]) = bottom + 4;
	}
	w->children[w->count] = id;
	w->count++;
	return 1;
}
