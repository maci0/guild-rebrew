#include <string.h>

#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046fdf0_Ent;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl d2_AllocateElement(void);
int __cdecl d2_MeasureTextWidth(char* s, int font);
void __cdecl d2_InsertControlAfterWindow(int slot, D2_WIN* parent);

/* ADDRESS: GOLDTL 0x0046fdf0 */
int __cdecl d2_AddWindowText(int x, int y, char* text, int win)
{
	D2_WIN* w;
	int id;

	w = &((D2_WIN*)d2_Windows)[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	id = d2_AllocateElement();
	strcpy(((char*)&((D2_CONTROL_TL*)d2_Controls)[id] + 0x90), text);
	if ((*(int*) &w->pad280[12]) != 0) {
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].font) = (*(int*) &w->pad280[12]);
	} else {
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].font) = d2_DefaultFont;
	}
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].kind) = 0x46;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].x) = w->left + x;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].y) = w->top - (*(int*) &w->pad3c[0x21c]) + y;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].width) = d2_MeasureTextWidth(text, (*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].font)) + 0x60;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) = d2_FontHeight;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].mode) = 2;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].parent) = (int) w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].data) = (int) w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_top) = 0;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_bottom) = d2_ScreenHeight;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_left) = 0;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_right) = g_1040494;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_050) = (*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->slot].value_050);
	d2_InsertControlAfterWindow(id, w);
	w->children[w->count] = id;
	w->count++;
	return id;
}
