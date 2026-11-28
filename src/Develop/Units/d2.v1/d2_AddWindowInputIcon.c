#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} D2_INPUT_ICON_ENT;
// SIZE 0x2f4

typedef struct
{
	int i[0x160 / 4];
} D2_INPUT_ICON_TEX;
// SIZE 0x160

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern char* d2_Controls;
extern Tex_102d278 g_102d278[];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl d2_OpenInputIcon(int x, int y, int a3, int a4, int a5);
void __cdecl d2_InsertControlAfterWindow(int slot, D2_WIN* parent);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00467480 */
/* ADDRESS: GOLDDE 0x0045aec0 */
int __cdecl d2_AddWindowInputIcon(int x, int y, int width, int height, int flags, int win)
{
	D2_WIN* par;
	int id;

	par = &((D2_WIN*)d2_Windows)[win];
	if (par->active == 0) {
		return -1;
	}
	if (par->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	id = d2_OpenInputIcon(par->left + x, par->top - (*(int*) &par->pad3c[0x21c]) + y, width, height, flags);
	d2_InsertControlAfterWindow(id, par);
	*(int*) (&((D2_CONTROL_TL*) d2_Controls)[id].parent) = (int) par;
	((D2_CONTROL_TL*) d2_Controls)[id].value_050 = ((D2_CONTROL_TL*) d2_Controls)[par->slot].value_050;
	((D2_CONTROL_TL*) d2_Controls)[id].clip_top = par->top;
	((D2_CONTROL_TL*) d2_Controls)[id].clip_bottom = par->height + par->top;
	((D2_CONTROL_TL*) d2_Controls)[id].clip_left = par->left;
	((D2_CONTROL_TL*) d2_Controls)[id].clip_right = par->width + par->left;
	((D2_INPUT_ICON_TEX*)g_102d278)[((D2_CONTROL_TL*) d2_Controls)[id].value_088].i[0] = (*(int*) &par->pad280[12]);
	((D2_INPUT_ICON_TEX*)g_102d278)[((D2_CONTROL_TL*) d2_Controls)[id].value_088].i[0x24 / 4] = par->width - ((D2_CONTROL_TL*) d2_Controls)[id].x - (*(int*) &par->pad14[8]) + par->left;
	par->children[par->count] = id;
	par->count++;
	return id;
}
