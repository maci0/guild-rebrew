

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
extern char g_77470d;
extern int g_7e46ac;
extern int g_772514;
extern char* g_77255c;
extern char* g_1015ea0;
extern int g_100f1dc;
extern List8c_102cbc8 g_102cbc8[];
extern char g_14cf950;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int, int, char *);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
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

int __cdecl fcn_005263d0(char *title, char *text, unsigned int flags)
{
	int mode;
	int h;
	int result;
	unsigned int start;
	int id;
	int f80;
	int list;
	int i;
	int k;

	start = (*(unsigned int*)&g_6b7fac);
	id = -1;
	result = 0;
	if (g_77470d != 0) {
		return 0;
	}
	mode = g_7e46ac & ~0x38;
	h = fcn_00470820(0, 0, "misc\\MessageBoxGreen");
	if (flags & 8) {
		mode = 0x717c6;
	}
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	if (title != 0) {
		fcn_00519190(title);
	}
	fcn_004727a0(h, 2);
	fcn_00519190(text);
	fcn_00471b60(h);
	g_77470d = 1;
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
	while (fcn_005373e0(fcn_005263d0, mode) != 0) {
		fcn_00469630(list);
		if (flags & 0x40) {
			fcn_004707d0(h);
		}
		if (g_100f1dc != 2) {
			if (g_100f1dc == 1 || g_14cf950 == 1) {
				g_774654 = 1;
				result = 0;
			}
		} else {
			g_774654 = 1;
			result = g_102cbc8[list].n + 1;
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
	g_77470d = 0;
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
