

#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0x24
typedef struct {
	unsigned short id;
	char pad2[0x1a];
	float f1c;
	int f20;
} Entry;

// SIZE 0x21c
typedef struct {
	char pad0[0x54];
	int f54;
	char pad58[0x1c4];
} House;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int shown;
	char pad60[0x170];
	int style;
	char pad1d4[0x11c];
	House* house;
} Slot;

extern char g_7f4ca0[];
extern char* g_1015ea0;
extern char s_6acc18[];
extern char s_6acc08[];
extern char s_6a9680[];
extern char s_67d444[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;

void __cdecl fcn_005091d0(int*, Entry*);
int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_005c9090(char*, int, int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005d46d0(void)
{
	int count;
	int dlg;
	int cols[8];
	char text[0x100];
	Entry list[8];
	int i;
	int fl;
	int h;
	int v;

	cols[0] = 0x8f;
	cols[1] = 0x95;
	cols[2] = 0x9b;
	cols[3] = 0xa1;
	cols[4] = 0xa7;
	cols[5] = 0xad;
	cols[6] = 0xb3;
	cols[7] = 0xb9;
	fcn_005091d0(&count, list);
	if (count == 0) {
		return;
	}
	if (!fcn_0057ec20(4)) {
		return;
	}
	fcn_0057e880(10, 0, 0, 0);
	if (count <= 6) {
		dlg = fcn_00470820(0, 0, s_6acc18);
	} else {
		dlg = fcn_00470820(0, 0, s_6acc08);
	}
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	fcn_004727a0(dlg, 1);
	fcn_00519190(0x1f35);
	fcn_004727a0(dlg, 2);
	for (i = 0; i < count; i++) {
		fl = (int) (list[i].f1c * 100.0f);
		h = fcn_0046f740(0x28, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2),
			((House*)g_7f4ca0)[list[i].id].f54, g_772514);
		((Slot*)g_1015ea0)[h].shown = 1;
		((Slot*)g_1015ea0)[h].style = 3;
		((Slot*)g_1015ea0)[h].house = &((House*)g_7f4ca0)[list[i].id];
		sprintf(text, s_6a9680, list[i].id);
		fcn_005c9090(text, 0x36, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 0x22, 0x12c, 0x56);
		v = MIN(MAX(((House*)g_7f4ca0)[list[i].id].f54 - 0x59a, 0), 7);
		h = fcn_004677e0(0x5a, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2) + 7, 0x12c, 0, 0x64,
			cols[v], 0x42, g_772514);
		fcn_00472380(h, 0, 0x64, fl);
		sprintf(text, s_67d444, list[i].f20);
		fcn_005c9090(text, 0x1f4, (count <= 4 ? 0x50 : 0x3a) * i + (count <= 4 ? 0x14 : 2), 0xc8, 0x55);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d46d0, 0x657c7) != 0);
	fcn_00471e30(dlg);
	fcn_0057e880(10, 0, 1, 0);
}
