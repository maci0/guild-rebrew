// FUNCTION: GOLDTL 0x00591190
// SIZE: 592

extern char* g_99ec10;
#include "client_types.h"
extern Obj_1038140 g_1038140[];
extern Win_1015f40 g_1015f40[0x60];
extern int g_1040494;
extern int g_772514;
extern int g_7747b4;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7e2aa0;
extern unsigned char* g_868050;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00519190(int, ...);
double __cdecl fcn_0050b980(int, int);

int __cdecl fcn_00591190(int id)
{
	int dlg;
	char* p;
	char* rec;
	unsigned char* sel;
	char* r;
	int k;
	int a;
	int b;
	float f;

	if (g_99ec10[id * 65] == 0x1d) {
		return -1;
	}
	dlg = fcn_00470820(0, 0, "ToolTip\\ToolTip_Objekte_Upgrades");
	fcn_00471b60(dlg);
	p = ((char*)g_1015f40) + *(int*) (((char*)g_1038140) + dlg * 700 + 4) * 972;
	if (*(int*) (p + 4) + *(int*) (p + 0xc) > g_1040494 - 16) {
		fcn_00469c40(g_1040494 - *(int*) (p + 0xc) - 16, *(int*) (p + 8), *(int*) (p + 0x27c));
	}
	fcn_004727a0(0, 2);
	fcn_0046f740(0, 0, id + 0xdf, g_772514);
	fcn_00519190(id * 2 + 0x9a9);
	fcn_004727a0(0, 1);
	fcn_00519190(id * 2 + 0x9a8);
	rec = g_99ec10 + id * 65;
	fcn_004727a0(0, 3);
	if (rec[0x40] != 0) {
		fcn_00519190(0x21, (unsigned char) rec[0x40]);
	} else {
		f = g_7747b4 * 0.25 + 0.5;
		fcn_00519190(0x23, (int) (fcn_0050b980(id, 100) * f));
	}
	fcn_00519190(0x20, *(int*) (rec + 0x22));
	sel = ((unsigned char*)g_7746c4);
	if (sel == 0) {
		sel = g_7746c8;
	}
	if (sel == 0) {
		sel = ((unsigned char*)g_7e2aa0);
	}
	if (sel != 0 && rec[0] != 2 && rec[0] != 6) {
		r = ((char*)g_868050) + *sel * 589;
		for (k = 0; k < 64; k++) {
			if ((*(unsigned short*) (r + 0x23 + k * 2) & 0x7fff) == id) {
				a = (unsigned char) r[k + 0x1a3];
				b = (unsigned char) r[k + 0x1e3];
				if (a != 0 && a != -1 && a != 0xff) {
					fcn_00519190(0x24);
					if (a == 3) {
						fcn_00519190((int) "+%a %s$N", b, 0xf9e);
					} else if (a == 0x24) {
						fcn_00519190((int) "+%i %s$N", b, 0xfe0);
					} else {
						fcn_00519190((int) "%i%% %s$N", b, a * 2 + 0xf98);
					}
				}
				break;
			}
		}
	}
	return dlg;
}
