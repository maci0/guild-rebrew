#include <windows.h>
#include <string.h>

extern char g_7e22c0[];      /* ini file path */
extern char g_7e23ea[];      /* first name buffer (0x20) */
extern char g_7e240a[];      /* family name buffer (0x20) */
extern char g_14cf950;       /* last pressed key */
extern int g_14ce8e0;
extern int g_100f1dc;        /* focused element id */
extern int g_67d370;
extern int g_774654;
extern int* g_774a34;        /* entity list head */
extern int* g_779cb8;        /* rejected entity */
extern int* g_779ce4;
extern char* g_100f1e4;      /* element of the current player */
extern int g_102cbc8[];
extern int g_102cbcc[];
extern char g_1015f4c[];
extern int g_772514;
extern char g_7e23e0;
extern char g_7e23e1;
extern char g_7e23e2;
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern int g_14abe74;
extern int g_14abe78;
extern int g_14abe80;
extern int g_14abe84;
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00517b10(char*, char*);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00533a60(int, int, void*, int, int, int);
int __cdecl fcn_004693b0(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00472770(int, int);
void __cdecl fcn_00473660(void);
void __cdecl fcn_00474cf0(int);
int __cdecl fcn_00472170(int, int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_004ce190(int);
int __cdecl fcn_004ce1d0(void);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004ce180(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
char* __cdecl itoa(int, char*, int);

/* ADDRESS: GOLDTL 0x005936f0 */

/* Player name editor: loads the stored name, religion, sex and crest, lays out
 * the eight crest buttons and runs the modal edit loop until the dialog
 * closes, then writes the selected name back to the ini file. */
int __cdecl fcn_005936f0(int msg, int param)
{
	char text[0x104];
	char digit[0x14];
	char* out[2];
	int ids[8];
	int first;
	int second;
	int elem6;
	int group;
	int h;
	int w8;
	int w24;
	int cols;
	int sel;
	int result;
	int i;
	int n;
	int p;
	char redraw;
	char* s;
	char* ep;
	char* np;
	int* ent;

	result = 0;
	sel = 0;
	redraw = 1;
	GetPrivateProfileStringA("Network", "Name", "Vorname", g_7e23ea, 0x20, g_7e22c0);
	GetPrivateProfileStringA("Network", "Familienname", "Nachname", g_7e240a, 0x20, g_7e22c0);
	g_7e23e4 = GetPrivateProfileIntA("Network", "Wappen", 0, g_7e22c0) + 0x59a;
	g_7e23e8 = (char) GetPrivateProfileIntA("Network", "Geschlecht", 0, g_7e22c0);
	g_7e23e9 = (char) GetPrivateProfileIntA("Network", "Glauben", 0, g_7e22c0);
	h = fcn_00470820(0, 0, "Menu\\CHOOSEPLAYER");
	fcn_00471b60(h);
	fcn_00517b10((char*) 0x9baa76, text);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1acf, text);
	first = fcn_00472250(h, 1, fcn_00519190(0x1ad0, 0x1ad2));
	fcn_004727a0(h, 2);
	second = fcn_00472250(h, 2, fcn_00519190(0x1ad1, 0x1ad3));
	fcn_004727a0(h, 3);
	fcn_00519190(0x1ad4);
	fcn_00533a60(g_772514, 0x1c, out, 2, g_14abe74, g_14abe78);
	np = out[0];
	s = out[1];
	fcn_004727a0(h, 4);
	fcn_00519190(0x1ad7);
	fcn_00533a60(g_772514, 0x1c, out, 2, g_14abe80, g_14abe84);
	ep = out[1];
	n = (int) out[0];
	fcn_004727a0(h, 5);
	fcn_00519190(0x1adb);
	cols = (*(int*) (g_772514 * 0x3cc + (int) g_1015f4c) - 0x20) / 0x30;
	group = fcn_004693b0(0);
	for (i = 0; i < 8; i++) {
		ids[i] = fcn_0046f740((i % cols) * 0x30 + 0x50, (i / cols) * 0x30 + 0x20, i + 0x59a, g_772514);
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x58) = 1;
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x38) = 0;
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x3c) = 0;
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x60) = 1;
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x1d0) = 3;
		fcn_00469470(group, ids[i]);
	}
	fcn_004727a0(h, 6);
	elem6 = fcn_00472250(h, 6, fcn_00519190(0x7e));
	d2_SetElementValue(first, g_7e23ea);
	d2_SetElementValue(second, g_7e240a);
	for (i = 0; i < 8; i++) {
		if (*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 8) == g_7e23e4) {
			fcn_004695a0(group, i);
			break;
		}
	}
	fcn_00472770(first, 0xc);
	fcn_00472770(second, 0xc);
	w8 = fcn_004693b0(2, np, s);
	fcn_004695a0(w8, g_7e23e8 & 0xff);
	w24 = fcn_004693b0(2, n, ep);
	fcn_004695a0(w24, g_7e23e9 & 0xff);
	fcn_00473660();
	g_14cf950 = 0;
	for (i = 0; i < 8; i++)
		*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x4c) = 0;
	for (p = 1; p < 9; p++) {
		ent = (int*) g_774a34[p];
		if (ent != 0) {
			n = fcn_004ce190((int) ent);
			if (n != 0) {
				if (*(int*) n != 0 && (int*) n != g_779cb8) {
					*(int*) (g_1015ea0 + ids[*(int*) (n + 0xc)] * 0x2f4 + 0x4c) = 1;
					if (*(int*) (g_1015ea0 + ids[*(int*) (n + 0xc)] * 0x2f4 + 0x38) != 0) {
						*(int*) (g_1015ea0 + ids[*(int*) (n + 0xc)] * 0x2f4 + 0x38) = 0;
						*(int*) (g_1015ea0 + ids[g_779cb8[3]] * 0x2f4 + 0x38) = 1;
					}
				}
			}
		}
	}
	for (;;) {
		if (g_779ce4[1] != 0) {
			g_779ce4[1] = 0;
			p = fcn_004ce1d0();
			n = fcn_004c4450(p);
			while (n == 0) {
				fcn_00535960();
				n = fcn_004c4450(p);
			}
			g_774a34 = (int*) fcn_004ce180();
			for (i = 0; i < 8; i++)
				*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x4c) = 0;
			for (p = 1; p < 9; p++) {
				ent = (int*) g_774a34[p];
				if (ent != 0) {
					n = fcn_004ce190((int) ent);
					if (n != 0) {
						if (*(int*) n != 0 && (int*) n != g_779cb8) {
							*(int*) (g_1015ea0 + ids[*(int*) (n + 0xc)] * 0x2f4 + 0x4c) = 1;
							*(int*) (g_1015ea0 + ids[*(int*) (n + 0xc)] * 0x2f4 + 0x38) = 0;
						}
					}
				}
			}
		}
		if (g_14ce8e0 != 0 || (g_100f1dc != -1 && g_67d370 == elem6) || g_14cf950 == 1) {
			if (sel == 0) {
				g_774654 = 1;
				if (!redraw)
					goto dispatch;
			}
			else {
				sel = sel - 1;
				goto update;
			}
		}
		else if (!redraw)
			goto dispatch;
update:
		for (i = 0; i < 5; i++)
			fcn_00472170(fcn_00472250(h, 0, i), i <= sel);
		if (sel == 0)
			fcn_00474cf0(first);
		else if (sel == 1)
			fcn_00474cf0(second);
		redraw = 0;
dispatch:
		if (sel == 0) {
			if (g_14cf950 == 0x1c) {
				s = fcn_00471f80(first);
				strcpy(g_7e23ea, s);
				sel = 1;
				redraw = 1;
				g_14cf950 = 0;
			}
		}
		else if (sel == 1) {
			if (g_14cf950 == 0x1c) {
				s = fcn_00471f80(second);
				strcpy(g_7e240a, s);
				sel = 2;
				redraw = 1;
				g_14cf950 = 0;
			}
		}
		else if (sel == 2) {
			fcn_00469630(second);
			if (g_100f1dc != -1) {
				if (g_67d370 == np) {
					g_7e23e8 = 0;
					sel = 3;
					redraw = 1;
				}
				else if (g_67d370 == s) {
					g_7e23e8 = 1;
					sel = 3;
					redraw = 1;
				}
			}
		}
		else if (sel == 3) {
			fcn_00469630(w8);
			if (g_100f1dc != -1) {
				if (g_67d370 == n) {
					g_7e23e9 = 1;
					sel = 4;
					redraw = 1;
				}
				else if (g_67d370 == ep) {
					g_7e23e9 = 0;
					sel = 4;
					redraw = 1;
				}
			}
		}
		else if (sel == 4) {
			fcn_00469630(group);
			if (g_14cf950 == 0x1c) {
				sel = 5;
				redraw = 1;
			}
			if (g_100f1dc >= 0x59a && g_100f1dc <= 0x5a1) {
				for (i = 0; i < 8; i++) {
					if (g_1015ea0 + ids[i] * 0x2f4 != g_100f1e4) {
						*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x38) = 0;
						*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x3c) = 0;
						*(int*) (g_1015ea0 + ids[i] * 0x2f4 + 0x60) = 1;
					}
				}
				sel = sel + 1;
			}
		}
		else if (sel == 5) {
			g_7e23e0 = 0;
			g_7e23e1 = 0;
			g_7e23e2 = 0x12;
			g_7e23e4 = *(int*) (g_1015ea0 + g_102cbcc[group * 35 + g_102cbc8[group * 35]] * 0x2f4 + 8);
			result = 1;
			g_774654 = 1;
		}
		if (fcn_005373e0((int (__cdecl*)(void)) 0x53d490, msg) == 0) {
			fcn_00469510(w8);
			fcn_00469510(w24);
			fcn_00469510(group);
			fcn_00471e30(h);
			WritePrivateProfileStringA("Network", "Name", g_7e23ea, g_7e22c0);
			WritePrivateProfileStringA("Network", "Familienname", g_7e240a, g_7e22c0);
			itoa(g_7e23e4 - 0x59a, digit, 10);
			WritePrivateProfileStringA("Network", "Wappen", digit, g_7e22c0);
			itoa(g_7e23e8 & 0xff, digit, 10);
			WritePrivateProfileStringA("Network", "Geschlecht", digit, g_7e22c0);
			itoa(g_7e23e9 & 0xff, digit, 10);
			WritePrivateProfileStringA("Network", "Glauben", digit, g_7e22c0);
			return result;
		}
	}
}
