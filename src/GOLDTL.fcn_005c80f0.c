

#include <string.h>
#pragma intrinsic(memset)

#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x4c];
	int district;
	char pad58[0x1c4];
} House5c80;

#define HOUSES 768
#define DISTRICT0 0x59a

extern Group_102cbc4 g_102cbc4[8];
extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_772514;
extern int g_100f1dc;
extern int g_774654;
extern char* g_aed32c;
extern char g_6ac80c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004693b0(int n, ...);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
void __cdecl fcn_00469470(int g, int id);
void __cdecl fcn_00472640(int i, int flag);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00525ef0(void);
void __cdecl fcn_004c4510(House5c80* p, int n);
int __cdecl fcn_004c4700(int type, int count, int off, char* data);
int __cdecl fcn_004c53a0(void);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004c5790(int, void*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469510(int i);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005c80f0(void)
{
	int back;
	int grp;
	int district;
	int d;
	int btn[8];
	int ev[0x1f];
	int j;
	House5c80* me_h;
	int i;
	int b;
	int found;
	int r;

	d = fcn_00470820(0, 0, g_6ac80c);
	fcn_00471b60(d);
	fcn_004727a0(d, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(d, 1);
	fcn_00519190(0x85);
	fcn_004727a0(d, 2);
	grp = fcn_004693b0(0);
	for (i = 0; i < 8; i++) {
		btn[i] = fcn_0046f740(i * 0x30 + 10, 0x78, i + DISTRICT0, g_772514);
		fcn_00469470(grp, btn[i]);
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < HOUSES; j++) {
			if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == DISTRICT0 - i && ((House5c80*)g_7f4ca0)[j].id != g_774970
				&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
				fcn_00472640(btn[i], 0);
			}
		}
	}
	fcn_004727a0(d, 3);
	back = fcn_00472250(d, 3, fcn_00519190(0x7f));
	g_102cbc4[grp].sel = -1;
	fcn_00525ef0();
	do {
		for (i = 0; i < 8; i++) {
			b = btn[i];
			fcn_00472640(b, 1);
			for (j = 0; j < HOUSES; j++) {
				if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == i + DISTRICT0 && ((House5c80*)g_7f4ca0)[j].id != g_774970
					&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
					fcn_00472640(b, 0);
				}
			}
		}
		if (g_102cbc4[grp].sel != -1) {
			fcn_00472640(back, 1);
		}
		else {
			fcn_00472640(back, 0);
		}
		if (g_100f1dc == 2 && g_102cbc4[grp].sel != -1) {
			me_h = &((House5c80*)g_7f4ca0)[g_774970];
			district = g_102cbc4[grp].sel + DISTRICT0;
			found = 0;
			fcn_004c4510(me_h, me_h->handle);
			fcn_004c4700(4, 1, (char*) me_h - g_aed32c + 0x54, (char*) &district);
			r = fcn_004c53a0();
			while (fcn_004c4450(r) == 0) {
				fcn_00535960();
			}
			for (i = 8; i != 0; i--) {
				for (j = 0; j < HOUSES; j++) {
					if (((House5c80*)g_7f4ca0)[j].id != 0xffff && ((House5c80*)g_7f4ca0)[j].district == g_102cbc4[grp].sel + DISTRICT0 && ((House5c80*)g_7f4ca0)[j].id != g_774970
						&& (((House5c80*)g_7f4ca0)[j].type == 6 || ((House5c80*)g_7f4ca0)[j].type == 7 || ((House5c80*)g_7f4ca0)[j].type == 5)) {
						found = 1;
					}
				}
			}
			if (found == 0) {
				g_774654 = 1;
				memset(ev, 0, sizeof(ev));
				ev[0] = g_774970;
				fcn_004c5790(0xd, ev);
			}
		}
	} while (fcn_005373e0(fcn_005c80f0, 0x677c7) != 0);
	fcn_00469510(grp);
	fcn_00471e30(d);
}
