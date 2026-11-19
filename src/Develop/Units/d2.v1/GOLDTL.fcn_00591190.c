

extern char* lpObjektePROT;
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern Obj_1038140 g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern int g_1040494;
extern int d2_CurrentWindowId;
extern int g_7747b4;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7e2aa0;
extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_0046f740(int, int, int, int);
int __cdecl io_AppendText(int, ...);
double __cdecl eval_ObjektPreis2Credits(int, int);

int __cdecl fcn_00591190(int id)
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

	if (lpObjektePROT[id * 65] == 0x1d) {
		return -1;
	}
	dlg = fcn_00470820(0, 0, "ToolTip\\ToolTip_Objekte_Upgrades");
	d2_CenterDialogWindows(dlg);
	p = &((D2_WIN*)g_1015f40)[*(int*) (((char*)g_1038140) + dlg * 700 + 4)];
	if (p->left + p->width > g_1040494 - 16) {
		fcn_00469c40(g_1040494 - p->width - 16, p->top, p->slot);
	}
	d2_SetForm(0, 2);
	fcn_0046f740(0, 0, id + 0xdf, d2_CurrentWindowId);
	io_AppendText(id * 2 + 0x9a9);
	d2_SetForm(0, 1);
	io_AppendText(id * 2 + 0x9a8);
	rec = lpObjektePROT + id * 65;
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
		r = ((char*)lpGebaeudePROT) + *sel * 589;
		for (k = 0; k < 64; k++) {
			if ((*(unsigned short*) (r + 0x23 + k * 2) & 0x7fff) == id) {
				a = (unsigned char) r[k + 0x1a3];
				b = (unsigned char) r[k + 0x1e3];
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
