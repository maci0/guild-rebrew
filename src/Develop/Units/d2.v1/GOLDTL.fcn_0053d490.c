#include <windows.h>
#include <stdlib.h>
#include <string.h>

extern int g_100f1dc;
extern int g_100f1e4;
extern char* g_1015ea0;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_67d370;
extern int g_772514;
extern int g_774654;
extern char g_7e22c0[];
extern char g_7e23ea[];
extern char g_7e240a[];
extern int g_7e23e4;
extern char g_7e23e8;
extern char g_7e23e9;
extern char g_7e23e0[];
extern char g_7e1d00[];

extern char s_6a1e4c[]; /* "Network" */
extern char s_6a1e54[]; /* "Name" */
extern char s_6a1e3c[]; /* "Familienname" */
extern char s_6a401c[]; /* "Vorname" */
extern char s_6a4010[]; /* "Nachname" */
extern char s_6a4008[]; /* "Wappen" */
extern char s_6a3ffc[]; /* "Geschlecht" */
extern char s_6a3ff4[]; /* "Glauben" */
extern char s_6a3fe0[]; /* "Menu\\CHOOSEPLAYER" */

int __cdecl d2_CreateRadioGroup(int, ...);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, ...);
void __cdecl fcn_00472770(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00476b60(void);
void __cdecl fcn_00474cf0(int);
int __cdecl fcn_00517b10(char*, char*);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00533a60(int, int, int*, int, int, int);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);

/* ADDRESS: GOLDTL 0x0053d490 */
int __cdecl fcn_0053d490(int a0, int a1)
{
	int list;
	int glyphs;
	int list1;
	int list2;
	char* s1a;
	char* s1b;
	char* s2a;
	char* s2b;
	int dlg;
	int v20;
	int v21;
	int v27;
	int i;
	int j;
	int n;
	int id;
	int rows;
	int v11[2];
	int sel[8];
	int v9;
	unsigned char redraw;
	int result;
	char itoa_buf[0x30];
	char buf[0xf0];

	redraw = 1;
	result = 0;
	sel[0] = 0;
	i = 0;
	list = 0;
	v9 = 0;
	GetPrivateProfileStringA(s_6a1e4c, s_6a1e54, s_6a401c, g_7e23ea, 0x20,
	    g_7e22c0);
	GetPrivateProfileStringA(s_6a1e4c, s_6a1e3c, s_6a4010, g_7e240a, 0x20,
	    g_7e22c0);
	g_7e23e4 = GetPrivateProfileIntA(s_6a1e4c, s_6a4008, 0, g_7e22c0) + 0x59a;
	g_7e23e8 = GetPrivateProfileIntA(s_6a1e4c, s_6a3ffc, 0, g_7e22c0);
	g_7e23e9 = GetPrivateProfileIntA(s_6a1e4c, s_6a3ff4, 0, g_7e22c0);
	dlg = fcn_00470820(0, 0, s_6a3fe0);
	fcn_00471b60(dlg);
	fcn_00517b10(g_7e1d00, buf);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x1acf, buf);
	v20 = fcn_00472250(dlg, 1, fcn_00519190(0x1ad0, 0x1ad2));
	d2_SetForm(dlg, 2);
	v21 = fcn_00472250(dlg, 2, fcn_00519190(0x1ad1, 0x1ad3));
	d2_SetForm(dlg, 3);
	fcn_00519190(0x1ad4);
	fcn_00533a60(g_772514, 0x1c, v11, 2, *(int*) 0x14abe74,
	    *(int*) 0x14abe78);
	s1a = (char*) v11[0];
	s1b = (char*) v11[1];
	d2_SetForm(dlg, 4);
	fcn_00519190(0x1ad7);
	fcn_00533a60(g_772514, 0x1c, v11, 2, *(int*) 0x14abe80,
	    *(int*) 0x14abe84);
	s2a = (char*) v11[0];
	s2b = (char*) v11[1];
	d2_SetForm(dlg, 5);
	fcn_00519190(0x1adb);
	rows = (*(int*) (g_772514 * 0x3cc + 0x1015f4c) - 0x20) / 0x30;
	list = d2_CreateRadioGroup(0);
	for (i = 0; i < 8; i++) {
		id = fcn_0046f740((i % rows) * 0x30 + 0x50,
		    (i / rows) * 0x30 + 0x20, i + 0x59a, g_772514);
		sel[i] = id;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x58) = 1;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x38) = 0;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x3c) = 0;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x60) = 1;
		*(int*) (g_1015ea0 + id * 0x2f4 + 0x1d0) = 3;
		fcn_00469470(list, id);
	}
	d2_SetForm(dlg, 6);
	v27 = fcn_00472250(dlg, 6, fcn_00519190(0x7e));
	fcn_00472380(v20, g_7e23ea);
	fcn_00472380(v21, g_7e240a);
	for (j = 0; j < 8; j++) {
		if (*(int*) (g_1015ea0 + sel[j] * 0x2f4 + 8) == g_7e23e4) {
			fcn_004695a0(list, j);
			break;
		}
	}
	fcn_00472770(v20, 0xc);
	fcn_00472770(v21, 0xc);
	list1 = d2_CreateRadioGroup(2, s1a, s1b);
	fcn_004695a0(list1, g_7e23e8 & 0xff);
	list2 = d2_CreateRadioGroup(2, s2a, s2b);
	fcn_004695a0(list2, g_7e23e9);
	fcn_00476b60();
	g_14cf950 = 0;
	for (;;) {
		if (g_14ce8e0 != 0
		    || (g_100f1dc != -1 && g_67d370 == v27)
		    || g_14cf950 == 1) {
			if (v9 == 0 && a1 == 0) {
				g_774654 = 1;
				goto check_redraw;
			}
			v9--;
			goto redraw_ui;
		}
	check_redraw:
		if (redraw == 0) {
			goto state_machine;
		}
	redraw_ui:
		for (i = 0; i < 5; i++) {
			fcn_00472170(fcn_00472250(dlg, 0, i), i <= v9);
		}
		if (v9 == 0) {
			fcn_00474cf0(v20);
		} else if (v9 == 1) {
			fcn_00474cf0(v21);
		}
		redraw = 0;
	state_machine:
		if (v9 == 0) {
			if (g_14cf950 == 0x1c) {
				strcpy(g_7e23ea, fcn_00471f80(v20));
				v9 = 1;
				redraw = 1;
				g_14cf950 = 0;
			}
		} else if (v9 == 1) {
			if (g_14cf950 == 0x1c) {
				strcpy(g_7e240a, fcn_00471f80(v21));
				v9 = 2;
				redraw = 1;
				g_14cf950 = 0;
			}
		} else if (v9 == 2) {
			fcn_00469630(list1);
			if (g_100f1dc != -1) {
				if (g_67d370 == (int) s1a) {
					g_7e23e8 = 0;
					v9 = 3;
					redraw = 1;
				} else if (g_67d370 == (int) s1b) {
					g_7e23e8 = 1;
					v9 = 3;
					redraw = 1;
				}
			}
		} else if (v9 == 3) {
			fcn_00469630(list2);
			if (g_100f1dc != -1) {
				if (g_67d370 == (int) s2b) {
					g_7e23e9 = 1;
					v9 = 4;
					redraw = 1;
				} else if (g_67d370 == (int) s2a) {
					g_7e23e9 = 0;
					v9 = 4;
					redraw = 1;
				}
			}
		} else if (v9 == 4) {
			fcn_00469630(list);
			if (g_14cf950 == 0x1c) {
				v9 = 5;
				redraw = 1;
			}
			if (0x59a <= g_100f1dc && g_100f1dc <= 0x5a1) {
				for (j = 0; j < 8; j++) {
					n = sel[j] * 0x2f4;
					if (g_1015ea0 + n != (char*) g_100f1e4) {
						*(int*) (g_1015ea0 + n + 0x38) = 0;
						*(int*) (g_1015ea0 + n + 0x3c) = 0;
						*(int*) (g_1015ea0 + n + 0x60) = 1;
					}
				}
				v9++;
			}
		} else if (v9 == 5) {
			g_7e23e0[0] = 0;
			*(unsigned char*) 0x7e23e1 = 0;
			*(unsigned char*) 0x7e23e2 = 0x12;
			g_7e23e4 = *(int*) (g_1015ea0
			    + *(int*) (((list * 8 - list) * 5
					   + *(int*) (list * 0x8c + 0x102cbc8)) * 4
				       + 0x102cbcc)
				* 0x2f4
			    + 8);
			result = 1;
			g_774654 = 1;
		}
		if (fcn_005373e0((int (__cdecl*)(void)) fcn_0053d490, a0) != 0) {
			continue;
		}
		fcn_00469510(list1);
		fcn_00469510(list2);
		fcn_00469510(list);
		fcn_00471e30(dlg);
		WritePrivateProfileStringA(s_6a1e4c, s_6a1e54, g_7e23ea,
		    g_7e22c0);
		WritePrivateProfileStringA(s_6a1e4c, s_6a1e3c, g_7e240a,
		    g_7e22c0);
		itoa(g_7e23e4 - 0x59a, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a4008, itoa_buf,
		    g_7e22c0);
		itoa(g_7e23e8 & 0xff, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a3ffc, itoa_buf,
		    g_7e22c0);
		itoa(g_7e23e9, itoa_buf, 10);
		WritePrivateProfileStringA(s_6a1e4c, s_6a3ff4, itoa_buf,
		    g_7e22c0);
		return result;
	}
}
