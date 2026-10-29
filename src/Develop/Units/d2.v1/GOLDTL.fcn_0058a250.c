#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

extern int g_772514;
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
#include "GOLDTL.fcn_0058a250_gconf.h"
extern char g_7f4ca4[];

void* __cdecl fcn_005cd440(void*, char*, int, int);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, ...);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_005898f0(void*);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float, int*);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* Builds the stock-trade dialog for the selected building, pumps the dialog
 * message loop and hands the scene back to the shared frame function. */
/* ADDRESS: GOLDTL 0x0058a250 */
void __cdecl fcn_0058a250(int a0)
{
	int ids[3];
	int q[20];
	char req[0x100];
	char* v6;
	int dlg;
	int elem;
	int v22;
	int v20;
	int v16;
	int sel;
	int id;
	int i;
	int n;

	for (i = 0; i < 20; i++) {
		q[i] = 0;
	}
	for (i = 7; i < 15; i++) {
		q[i] = -1;
	}
	q[0] = 1;
	q[1] = 0x400;
	q[4] = 6;
	v6 = (char*) fcn_005cd440(q, (char*) *(int*) 0x14b5310, 0, 0);
	if (v6 == 0) {
		fcn_00532ef0();
		return;
	}
	n = fcn_004e99c0(*(unsigned char*) (v6 + 0x166)) / 3;
	ids[0] = n + 5;
	ids[1] = n + 7;
	ids[2] = n + 10;
	dlg = fcn_00470820(0, 0, (char*) 0x6a9514);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 2);
	elem = d2_ShowTxt(0, 3, (char*) *(int*) 0x14b531c, g_772514);
	*(int*) (elem * 0x2f4 + (int) g_1015ea0 + 0x6c) = 1;
	*(int*) (elem * 0x2f4 + (int) g_1015ea0 + 0x18) = *(int*) (g_772514 * 0x3cc + 0x1015f4c);
	fcn_00472900(elem, 0x54);
	elem = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 2, g_772514);
	d2_SetElementValue(elem, 0, 2, 0, 1);
	fcn_00468bb0(elem, 3, *(int*) 0x14b5320, *(int*) 0x14b5324, *(int*) 0x14b5328);
	d2_SetForm(dlg, 3);
	v16 = fcn_00519190(0x4003);
	v22 = fcn_00472250(dlg, 3, v16);
	v20 = fcn_00472250(dlg, 3, v16 + 1);
	g_100f1dc = -1;
	do {
		v16 = fcn_00471f80(v16);
		d2_SetForm(dlg, 1);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x3ffd, 0x3ffb, *(unsigned short*) v6);
		fcn_00519190(0x3ffe, ids[v16]);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == v22) {
				if (fcn_00525f60(g_slot_table + g_774970 * 0x21c, v16) == 1 && fcn_005898f0((void*) a0) != 0) {
					fcn_005100f0(*(int*) (g_slot_table + g_774970 * 0x21c + 4), -v16);
					for (i = 0; i < 0x3e; i++) {
						*(int*) (req + 8 + i * 4) = 0;
					}
					req[4] = 0x99;
					req[0x36] = 2;
					*(int*) (req + 0x64) = -1;
					*(int*) (req + 0x68) = 1;
					*(int*) (req + 8) = *(int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + (int) g_7f4ca4);
					*(int*) (req + 0x2c) = g_7f4c04;
					*(int*) (req + 0x28) = g_7f4c00;
					*(int*) (req + 0xc) = *(int*) (v6 + 1);
					*(int*) (req + 0x5c) = *(int*) (v6 + 1);
					*(int*) (req + 0x30) = g_7f4c08;
					*(short*) (req + 0x34) = g_7f4c0c;
					*(int*) (req + 0x60) = *(int*) (v6 + 4);
					*(int*) (req + 0x6c) = v16;
					if (*(int*) (v6 + 0x170) != 0) {
						sel = *(int*) (*(int*) (v6 + 0x170) + 1);
					} else if (*(int*) (v6 + 0x16c) != 0) {
						sel = *(int*) (*(int*) (v6 + 0x16c) + 1);
					} else {
						v16 = -1;
						fcn_004a5e60((unsigned short*) (g_slot_table + g_774970 * 0x21c), 0, 0x7b4c4a0, 0, 0.0f, 100.0f, &v16);
						sel = v16;
					}
					*(int*) (req + 0x58) = sel;
					id = fcn_004c5530(req);
					if (id != -1) {
						while (fcn_004c4450(id) == 0) {
							fcn_005373e0(0, 0x20007);
						}
					}
					fcn_004c3030(-7, 0, (char*) 0x6a9508, 0);
				}
			} else if (g_67d370 == v20) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0058a250, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
