

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
typedef struct {
	char f0[4];
	int f4;
	char pad[0x214];
} Slot5c0d;

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_6ac494[];

int __cdecl fcn_0055c140(void*, unsigned short*, int*);
int __cdecl fcn_00579640(unsigned short*, void*);
int __cdecl fcn_00525f60(void*, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, void*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005c9220(int*);
int __cdecl fcn_005373e0(void*, int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005c0d90(unsigned short* obj)
{
	int res;
	int cnt;
	int arr[6];
	char text[0x400];
	int d;

	res = 0;
	if (obj == 0) {
		return 0;
	}
	if (*obj == 0xffff) {
		return 0;
	}
	if (*obj == g_774970) {
		return 0;
	}
	if (fcn_0055c140(&((Slot5c0d*)g_7f4ca0)[g_774970], obj, &cnt) == 0) {
		io_FormatTextBuffer(text, 0x190f, *obj);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_00579640(obj, &((Slot5c0d*)g_7f4ca0)[g_774970]) == 0) {
		io_FormatTextBuffer(text, 0x409f, *obj);
		fcn_00526120(text, 0);
		return 0;
	}
	if (cnt > 3) {
		io_FormatTextBuffer(text, 0x190e);
		fcn_00526120(text, 0);
		return 0;
	}
	if (fcn_00525f60(&((Slot5c0d*)g_7f4ca0)[g_774970], 1) == 0) {
		return 0;
	}
	d = fcn_00470820(0, 0, g_6ac494);
	fcn_00471b60(d);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(d, 1);
	io_AppendText(0x1910, *obj, *obj, 1, *obj);
	memset(arr, 0xff, sizeof(arr));
	arr[0] = d;
	arr[3] = 4;
	arr[4] = 4;
	arr[1] = 2;
	arr[2] = 3;
	arr[5] = 3;
	fcn_005c9220(arr);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				char ev[0xf8];

				gm_StartFilteredEntitySearch(1, 5, 0xa);
				ev[4] = 0x35;
				ev[0x36] = 2;
				*(int*) (ev + 8) = ((Slot5c0d*)g_7f4ca0)[g_774970].f4;
				*(int*) (ev + 0xc) = ((Slot5c0d*)g_7f4ca0)[g_774970].f4;
				*(int*) (ev + 0x58) = (*(int*)&g_7f4c00);
				*(int*) (ev + 0x5c) = (*(int*)&g_7f4c04);
				*(int*) (ev + 0x60) = g_7f4c08;
				*(short*) (ev + 0x64) = g_7f4c0c;
				ev[0x6d] = (char) gm_RandomMod(0x1d);
				*(int*) (ev + 0x68) = *(int*) (obj + 2);
				fcn_004c5530(ev);
				res = 1;
				g_774654 = 1;
			}
			else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005c0d90, 0x677c7) != 0);
	fcn_00471e30(d);
	return res;
}
