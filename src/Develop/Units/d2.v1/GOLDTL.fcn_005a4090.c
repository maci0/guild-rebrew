

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x214];
};

// SIZE 0xc
struct want {
	int n;
	int x;
	int y;
};

// SIZE 0x14
struct line {
	int n;
	int x;
	int y;
	int handle;
	int slot;
};

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern int g_14ab670;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_6aaba0[];

void __cdecl fcn_0050d6d0(char*, struct house*, int, struct want*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004c51a0(int, int, char, int);
int __cdecl fcn_004c5530(char* msg);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00471a30(int k, int flag);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005a4090(char* p)
{
	struct line list[3];
	char ev[0xf8];
	struct want src[3];
	int i;
	int h;
	int r;
	int j;

	memset(list, 0, sizeof(list));
	fcn_0050d6d0(p, &((struct house*)g_7f4ca0)[g_774970], 3, src);
	j = 0;
	for (i = 0; i < 3; i++) {
		if (src[i].n > 0) {
			list[j].n = src[i].n;
			list[j].x = src[i].x;
			list[j].y = src[i].y;
			list[j].slot = i;
			j++;
		}
	}
	h = fcn_00470820(0, 0, g_6aaba0);
	fcn_00471b60(h);
	d2_SetForm(h, 1);
	fcn_00519190(0x18d0);
	d2_SetForm(h, 2);
	fcn_00519190(0x18d1, *(unsigned short*) (p + 0x25), p);
	for (i = 0; i < 3; i++) {
		if (list[i].n > 0) {
			list[i].handle = fcn_00472250(h, 2, fcn_00519190(0x18d2, list[i].n, list[i].y, list[i].x, 0x5d));
		}
	}
	fcn_00519190(0x18d3);
	fcn_00473a90(0, 0);
	while (fcn_005373e0(fcn_005a4090, 0x677c7) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			for (i = 0; i < 3; i++) {
				if (list[i].n != 0 && g_67d370 == list[i].handle) {
					goto found;
				}
			}
			continue;
found:
			memset(ev, 0, sizeof(ev));
			ev[4] = 0x23;
			*(int*) (ev + 8) = ((struct house*)g_7f4ca0)[*(unsigned short*) (p + 0x27)].handle;
			*(int*) (ev + 0xc) = *(int*) (p + 1);
			*(int*) (ev + 0x28) = (*(int*)&g_7f4c00);
			*(int*) (ev + 0x2c) = (*(int*)&g_7f4c04);
			*(int*) (ev + 0x30) = g_7f4c08;
			*(short*) (ev + 0x34) = g_7f4c0c;
			ev[0x36] = 0x12;
			*(int*) (ev + 0x58) = *(int*) (p + 1);
			*(int*) (ev + 0x5c) = ((struct house*)g_7f4ca0)[g_774970].handle;
			*(int*) (ev + 0x60) = list[i].n;
			*(int*) (ev + 0x64) = list[i].x;
			*(int*) (ev + 0x6c) = list[i].y;
			fcn_004c51a0(((struct house*)g_7f4ca0)[g_774970].handle, *(int*) (p + 1), g_773d75, list[i].n);
			r = fcn_004c5530(ev);
			while (fcn_004c4450(r) == 0) {
				fcn_005373e0(0, 0x677c7);
			}
			fcn_00471a30(h, 0);
			fcn_00526120(g_14ab670, 4);
			fcn_00471a30(h, 1);
			*(int*) (p + list[i].slot * 0xc + 0x71) = -1;
			g_774654 = 1;
		}
		else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}
