

typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x270];
	int x28c;
	char pad290[0x3cc - 0x290];
} Win;
// SIZE 0x3cc

typedef struct
{
	int text;
	int icon;
	char* obj;
} Row;
// SIZE 0xc

typedef struct
{
	int x0;
	char pad4[8];
	int width;
} Screen;

extern char* g_772500;
extern char* g_77255c;
extern int g_772514;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_0050d5d0(int, int, char**);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00519190(int, ...);

void __cdecl fcn_005c9310(unsigned short* who, int max, Row* rows, int dlg, int n)
{
	char* list[9];
	int w;
	int i;
	int cnt;
	void* t;

	if (max >= 9) {
		max = 9;
	}
	cnt = fcn_0050d5d0(*who, 0, list);
	w = *(short*) (g_772500 + 0x269d8);
	if (cnt >= max) {
		cnt = max;
	}
	for (i = 0; i < cnt; i++) {
		d2_SetForm(dlg, n);
		rows[i].icon = fcn_0046f740((((Screen*)g_77255c)->width - w) >> 1, i * 0x80, 0x75a, g_772514);
		rows[i].text = fcn_0046f100((((Screen*)g_77255c)->width - w) >> 1, i * 0x80 + 4, w, 0x72, 0x10, g_772514);
		rows[i].obj = list[i];
		((Win*)g_1015f40)[rows[i].text].x28c = 0x56;
		((Win*)g_1015f40)[rows[i].text].x18 = 0x10;
		t = gm_SearchTable67(*(int*) (rows[i].obj + 0xac));
		if (t != 0) {
			fcn_00519190(0x1f41, t, *(int*) (rows[i].obj + 0xb4), *(int*) (rows[i].obj + 0xc0), rows[i].obj + 0xc4);
		}
	}
}
