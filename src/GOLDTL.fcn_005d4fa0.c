// FUNCTION: GOLD 0x005c8d10
// FUNCTION: GOLDTL 0x005d4fa0

#include <stdlib.h>
#include <string.h>

extern float g_6628ac;
extern unsigned char g_773d75;
extern char s_6acc44[];
extern char s_679060[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_004c6ae0(int, int);
int __cdecl fcn_004c5420(int, int, int, int, int);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_004c5150(int, int, char, int);
float __cdecl fcn_004ff210(unsigned short, int);
int __cdecl fcn_00508890(unsigned char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(unsigned char*, int);
int __cdecl fcn_00526010(unsigned char*, int, char);
void __cdecl fcn_0051af00(char*, ...);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005d4fa0(unsigned char* e)
{
	int money;
	int result;
	int dlg;
	char tmp[0x100];
	char text[0x400];
	int half;
	int id;
	int ok;
	int cancel;
	int h;

	result = 2;
	if (e[2] != 6 && e[2] != 7) {
		if (*(int*) (e + 0x194) < 2) {
			return 0;
		}
		half = abs(*(int*) (e + 0x24)) / 2;
		money = (int) (gm_WalkEntityChain(*(unsigned short*) e) * g_6628ac);
		fcn_004c6ae0(*(int*) (e + 4), -2);
		fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x40, 0);
		if (fcn_0042e410(2)) {
			fcn_004c5150(-1, *(int*) (e + 4), g_773d75, money);
			fcn_004ff210(*(unsigned short*) e, half);
			fcn_00508890(e);
		}
		return 0x11;
	}
	money = (int) (gm_WalkEntityChain(*(unsigned short*) e) * g_6628ac);
	dlg = fcn_00470820(0, 0, s_6acc44);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	id = fcn_00519190(0x1d3b, 2, money);
	ok = fcn_00472250(dlg, 1, id);
	cancel = fcn_00472250(dlg, 1, id + 1);
	g_100f1dc = -1;
	do {
		if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (fcn_00525f60(e, 2) && fcn_00526010(e, money, g_773d75)) {
					fcn_004c6ae0(*(int*) (e + 4), -2);
					fcn_0051af00(text, 0x1d3c);
					if (fcn_0042e410(2)) {
						fcn_0051af00(tmp, s_679060, 0x1d3d);
						strcat(text, tmp);
						fcn_004c5150(-1, *(int*) (e + 4), g_773d75, money);
						fcn_00508890(e);
					} else {
						fcn_0051af00(tmp, s_679060, 0x1d3e);
						strcat(text, tmp);
					}
					ok = -1;
					cancel = -1;
					result = 0x81;
					h = fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x40, 0);
					while (fcn_004c4450(h) == 0) {
						fcn_00535960();
					}
					fcn_00526120(text, 0);
					g_774654 = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d4fa0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	return result;
}
