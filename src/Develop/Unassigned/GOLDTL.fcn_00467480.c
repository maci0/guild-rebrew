#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00467480_Ent;
// SIZE 0x2f4

typedef struct
{
	int i[0x160 / 4];
} fcn_00467480_Fld;
// SIZE 0x160

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern Tex_102d278 g_102d278[];
extern char s_67d420[];

#include "Develop/Units/Error/error_message.h"
int __cdecl d2_OpenInputIcon(int x, int y, int a3, int a4, int a5);
void __cdecl fcn_0046f650(int slot, D2_WIN* parent);

/* ADDRESS: GOLDTL 0x00467480 */
int __cdecl fcn_00467480(int x, int y, int a3, int a4, int a5, int win)
{
	D2_WIN* par;
	int id;

	par = &((D2_WIN*)g_1015f40)[win];
	if (par->active == 0) {
		return -1;
	}
	if (par->count >= 0x180) {
		ReportClientMessage(s_67d420);
		return -1;
	}
	id = d2_OpenInputIcon(par->left + x, par->top - (*(int*) &par->pad3c[0x21c]) + y, a3, a4, a5);
	fcn_0046f650(id, par);
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x40 / 4] = (int) par;
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x50 / 4] = ((fcn_00467480_Ent*)g_1015ea0)[par->slot].i[0x50 / 4];
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x30 / 4] = par->top;
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x34 / 4] = par->height + par->top;
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x28 / 4] = par->left;
	((fcn_00467480_Ent*)g_1015ea0)[id].i[0x2c / 4] = par->width + par->left;
	((fcn_00467480_Fld*)g_102d278)[((fcn_00467480_Ent*)g_1015ea0)[id].i[0x88 / 4]].i[0] = (*(int*) &par->pad280[12]);
	((fcn_00467480_Fld*)g_102d278)[((fcn_00467480_Ent*)g_1015ea0)[id].i[0x88 / 4]].i[0x24 / 4] = par->width - ((fcn_00467480_Ent*)g_1015ea0)[id].i[0x10 / 4] - (*(int*) &par->pad14[8]) + par->left;
	par->children[par->count] = id;
	par->count++;
	return id;
}
