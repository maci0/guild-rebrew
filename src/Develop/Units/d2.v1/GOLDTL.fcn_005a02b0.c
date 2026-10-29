#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern float g_662cf8;
extern int g_772514;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(void*, int);
int __cdecl gm_GetOppositeStatIndex(int);
float __cdecl fcn_00507540(int, int*);
int __cdecl gm_MapEntityStatRange(int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00525ef0(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_0051af00(char*, int, int);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00532ef0(void);
/* ADDRESS: GOLDTL 0x005a02b0 */
int __cdecl fcn_005a02b0(void)
{
	float grade;
	int info[4];
	char msg[0xf8];
	char text[0x100];
	char* slot;
	int h;
	int n;
	int mode;
	int d;
	int base;
	int r;

	slot = (char*) 0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c;
	n = gm_GetOppositeStatIndex(*(unsigned char*) (slot + 0x164)) + 1;
	h = fcn_00470820(0, 0, (char*) 0x6aa80c);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	fcn_00525ef0();
	grade = fcn_00507540(*(unsigned short*) 0x774970, info);
	r = (int) fcn_005463a0(2, 2, *(unsigned short*) 0x774970, 0, 0x26);
	if (r == 0 && grade >= 1.0 && n <= 6) {
		base = *(char*) (slot + 9) != 0 ? 0x18f : 0x130;
		gm_MapEntityStatRange(*(unsigned char*) (slot + 0x164));
		d2_SetForm(h, 1);
		fcn_00519190(0x15bb);
		d2_SetForm(h, 2);
		fcn_00519190(0x15bf, *(unsigned short*) slot, 4,
		    base + *(unsigned char*) (slot + 0x164) - 1);
		if (n % 2 != 0) {
			fcn_00519190(0x15c0);
		}
		d2_SetForm(h, 3);
		fcn_00519190(0x15c1);
	}
	else if (r != 0) {
		d2_SetForm(h, 1);
		fcn_00519190(0x15bb);
		d2_SetForm(h, 2);
		base = *(char*) (slot + 9) != 0 ? 0x18f : 0x130;
		fcn_00519190(0x15bd, *(unsigned short*) slot,
		    base + *(unsigned char*) (slot + 0x164) - 1);
	}
	else {
		d2_SetForm(h, 1);
		fcn_00519190(0x15bb);
		d2_SetForm(h, 2);
		if (n >= 7) {
			fcn_00519190(0x15be, *(unsigned short*) slot);
		}
		else {
			fcn_00519190(0x15bc, *(unsigned short*) slot, info);
			d = fcn_004677e0(0x1c,
			    *(int*) (*(char**) 0x77255c + 0x10) - 0x3c,
			    *(int*) (*(char**) 0x77255c + 0xc) - 0x40, 0, 0x64, 0x83,
			    0x42, g_772514);
			d2_SetElementValue(d, 0, 0x64, (int) (grade * g_662cf8));
		}
	}
	while (fcn_005373e0((void*) fcn_005a02b0, 0x677c7) != 0) {
		if ((mode = *(int*) 0x100f1dc) != -1 && grade >= 1.0) {
			if (mode == 2) {
				if (*(int*) (slot + 0x194) < 4) {
					fcn_0051af00(text, 0x74, 4);
					fcn_00526120(text, 4);
				}
				else {
					fcn_005100f0(*(int*) (slot + 4), -4);
					memset(msg, 0, sizeof(msg));
					*(int*) (msg + 8) = *(int*) (slot + 4);
					*(int*) (msg + 0xc) = -1;
					*(pos14_7f4c00*) (msg + 0x28) = g_7f4c00;
					msg[4] = 0x26;
					msg[0x36] = 9;
					*(int*) (msg + 0x58) = *(int*) (slot + 4);
					fcn_00500bb0(msg + 0x28, 2, 0, 0);
					fcn_004c5530(msg);
					*(int*) 0x774654 = 1;
				}
			}
			else if (mode == 1) {
				*(int*) 0x774654 = 1;
			}
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
	}
	fcn_00471e30(h);
	return fcn_00532ef0();
}
