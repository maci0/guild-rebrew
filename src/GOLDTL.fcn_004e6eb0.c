// FUNCTION: GOLDTL 0x004e6eb0

typedef struct {
	char pad0[0xc];
	int w;
	int h;
	char pad14[0x14];
	int *ids;
	int count;
} Screen;
// SIZE 0x30

typedef struct {
	char pad0[0x20];
	int kind;
	char pad24[0x2d0];
} Obj2f4;
// SIZE 0x2f4

#include "client_types.h"
typedef List8c_102cbc8 List8c;
// SIZE 0x8c

extern int g_6b7fac;
extern char g_772f74;
extern int g_7e46ac;
extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern int g_100f894;
extern List8c_102cbc8 g_102cbc8[];
extern char g_14cf950;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00519190(char *);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004693b0(int);
void __cdecl fcn_00469470(int, int);
void __cdecl fcn_004695a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_005373e0(void *, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_004707d0(int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_004e6eb0(char *text, unsigned int flags)
{
	int mode;
	int result;
	unsigned int start;
	int id;
	int f80;
	int h;
	int me;
	int list;
	int i;
	int k;

	start = (*(unsigned int*)&g_6b7fac);
	id = -1;
	result = 0;
	if (g_772f74 != 0) {
		return 0;
	}
	mode = g_7e46ac & ~0x38;
	if (flags & 2) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_Autosize");
	} else if (flags & 0x10) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_BIG");
	} else if (flags & 0x20) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_VERY_BIG");
	} else if (flags & 0x100) {
		h = fcn_00470820(0, 0, "misc\\Messagebox_NONE_PERGA");
		fcn_004727a0(h, 1);
	} else {
		h = fcn_00470820(0, 0, "misc\\Messagebox");
	}
	if (flags & 8) {
		mode = 0x717c6;
	}
	fcn_00519190(text);
	me = g_772514;
	fcn_00471b60(h);
	g_772f74 = 1;
	list = fcn_004693b0(0);
	for (i = 0; i < ((Screen*)g_77255c)->count; i++) {
		k = ((Screen*)g_77255c)->ids[i];
		if (((Obj2f4*)g_1015ea0)[k].kind != 0x40) {
			fcn_00469470(list, k);
		}
	}
	fcn_004695a0(list, 0);
	fcn_004727a0(h, 0);
	f80 = flags & 0x80;
	if (f80) {
		id = fcn_004677e0(0x1c, ((Screen*)g_77255c)->h - 0x18, ((Screen*)g_77255c)->w - 0x40, 0, 500, 0x83, 0x42, g_772514);
	}
	while (fcn_005373e0(fcn_004e6eb0, mode) != 0) {
		fcn_00469630(list);
		if (flags & 0x40) {
			fcn_004707d0(h);
		}
		if (g_100f1dc == 2 && g_100f894 == me) {
			result = g_102cbc8[list].n + 1;
			g_774654 = 1;
		} else if ((g_100f1dc == 1 && g_100f894 == me) || g_14cf950 == 1) {
			result = 0;
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (f80 && id != -1) {
			fcn_00472380(id, 0, 500, (*(unsigned int*)&g_6b7fac) - start);
		}
		if ((flags & 4) && (*(unsigned int*)&g_6b7fac) > start + 500) {
			g_774654 = 1;
		}
	}
	g_772f74 = 0;
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
