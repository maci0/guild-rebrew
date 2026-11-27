#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern char* lpObjektePROT;
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern D2_FORM_RECORD g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern int g_1040494;
extern int d2_CurrentWindowId;
extern int g_7747b4;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7e2aa0;
extern unsigned char* lpGebaeudePROT;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl io_AppendText(int, ...);
double __cdecl eval_ObjektPreis2Credits(int, int);

int __cdecl d2_OpenObjektUpgradeTooltip(int id)
{
	int dlg;
	D2_WIN* p;
	char* rec;
	unsigned char* sel;
	char* r;
	int k;
	int a;
	int b;
	float f;

	if ((*(char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id].kind) == 0x1d) {
		return -1;
	}
	dlg = d2_LoadForm(0, 0, "ToolTip\\ToolTip_Objekte_Upgrades");
	d2_CenterDialogWindows(dlg);
	p = &((D2_WIN*)g_1015f40)[*(int*) (((char*)g_1038140) + dlg * 700 + 4)];
	if (p->left + p->width > g_1040494 - 16) {
		fcn_00469c40(g_1040494 - p->width - 16, p->top, p->slot);
	}
	d2_SetForm(0, 2);
	d2_AddElementToWindow(0, 0, id + 0xdf, d2_CurrentWindowId);
	io_AppendText(id * 2 + 0x9a9);
	d2_SetForm(0, 1);
	io_AppendText(id * 2 + 0x9a8);
	rec = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[id]);
	d2_SetForm(0, 3);
	if (rec[0x40] != 0) {
		io_AppendText(0x21, (unsigned char) rec[0x40]);
	} else {
		f = (float)(g_7747b4 * 0.25 + 0.5);
		io_AppendText(0x23, (int) (eval_ObjektPreis2Credits(id, 100) * f));
	}
	io_AppendText(0x20, *(int*) (rec + 0x22));
	sel = ((unsigned char*)g_7746c4);
	if (sel == 0) {
		sel = g_7746c8;
	}
	if (sel == 0) {
		sel = ((unsigned char*)g_7e2aa0);
	}
	if (sel != 0 && rec[0] != 2 && rec[0] != 6) {
		r = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*sel];
		for (k = 0; k < 64; k++) {
			if ((((BUILDING_PROTOTYPE*)r)->components[k] & 0x7fff) == id) {
				a = (unsigned char) ((BUILDING_PROTOTYPE*)r)->component_kind[k];
				b = (unsigned char) ((BUILDING_PROTOTYPE*)r)->component_value[k];
				if (a != 0 && a != -1 && a != 0xff) {
					io_AppendText(0x24);
					if (a == 3) {
						io_AppendText((int) "+%a %s$N", b, 0xf9e);
					} else if (a == 0x24) {
						io_AppendText((int) "+%i %s$N", b, 0xfe0);
					} else {
						io_AppendText((int) "%i%% %s$N", b, a * 2 + 0xf98);
					}
				}
				break;
			}
		}
	}
	return dlg;
}
