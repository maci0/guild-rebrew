

#include <stdio.h>
#include <string.h>

// SIZE 0x21c
typedef struct House {
	char pad0[2];
	char kind;
	char pad3;
	int f4;
	char pad8[0x4c];
	int f54;
	char pad58[0x1c4];
} House;

// SIZE 0x2f4
typedef struct Ctl {
	char pad0[0x58];
	int f58;
	char pad5c[0x294];
	House* house;
} Ctl;

// SIZE 0x80
typedef struct Chat {
	int names[8];
	char text[0x60];
} Chat;

extern char g_7f4ca0[];
extern char* g_1015ea0;
extern unsigned char g_6a2c14[8];
extern int g_6a2c1c;
extern int g_772514;
extern int g_14ac628;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern unsigned short g_774970;
extern char g_6b5c60[];
extern char g_7e3a60[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472770(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00474cf0(int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_004c6560(Chat*);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00536810(void)
{
	int ids[8];
	Chat chat;
	int dlg;
	int win;
	int edit;
	int n;
	int i;

	ids[0] = -1;
	ids[1] = -1;
	ids[2] = -1;
	ids[3] = -1;
	ids[4] = -1;
	ids[5] = -1;
	ids[6] = -1;
	ids[7] = -1;
	g_6a2c1c = 0;
	dlg = fcn_00470820(0, 0, "misc\\chatconsole");
	fcn_00471d80(dlg, 3);
	d2_SetForm(dlg, 3);
	n = 0;
	for (i = 0; i < 768; i++) {
		if (((House*) g_7f4ca0)[i].kind == 7) {
			ids[n] = fcn_0046f740(n * 0x30 + 0x64, 4, ((House*) g_7f4ca0)[i].f54, g_772514);
			((Ctl*) g_1015ea0)[ids[n]].f58 = 1;
			((Ctl*) g_1015ea0)[ids[n]].house = &((House*) g_7f4ca0)[i];
			d2_SetElementValue(ids[n], g_6a2c14[n]);
			n++;
		}
	}
	win = fcn_00468df0(0, 0, 0xc5, g_14ac628, g_772514);
	fcn_00472900(win, 0x54);
	d2_SetForm(dlg, 2);
	edit = fcn_00472250(dlg, 2, fcn_00519190(0x1cc3, g_6b5c60));
	fcn_00472770(edit, 0x60);
	while (fcn_005373e0(fcn_00536810, 0x657c7)) {
		d2_SetForm(dlg, 1);
		fcn_00519190((int) "$C");
		fcn_00519190((int) g_7e3a60);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		fcn_00474cf0(edit);
		if ((g_100f1dc != -1 || g_14cf950 == 0x1c) && (g_67d370 == win || g_14cf950 == 0x1c)) {
			for (i = 0; i < 8; i++) {
				if (ids[i] != -1 && fcn_00471f80(ids[i]) != 0) {
					chat.names[i] = ((Ctl*) g_1015ea0)[ids[i]].house->f4;
				}
			}
			sprintf(chat.text, "$%iFF ", ((House*) g_7f4ca0)[g_774970].f54 - 0x59a);
			strcat(chat.text, fcn_00471f80(edit));
			strcat(chat.text, "$A");
			d2_SetElementValue(edit, g_6b5c60);
			fcn_004c6560(&chat);
			g_774654 = 1;
		}
	}
	for (i = 0; i < 8; i++) {
		if (ids[i] != -1) {
			g_6a2c14[i] = (unsigned char) fcn_00471f80(ids[i]);
		}
	}
	fcn_00471e30(dlg);
	g_14cf950 = 0;
}
