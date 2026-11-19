

#include "Develop/Units/d2.v1/d2_win.h"








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
extern int d2_CurrentWindowId;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_0050d5d0(int, int, char**);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046f100(int, int, int, int, int, int);
void* __cdecl gm_SearchTable67(int);
int __cdecl io_AppendText(int, ...);

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
		rows[i].icon = fcn_0046f740((((Screen*)g_77255c)->width - w) >> 1, i * 0x80, 0x75a, d2_CurrentWindowId);
		rows[i].text = fcn_0046f100((((Screen*)g_77255c)->width - w) >> 1, i * 0x80 + 4, w, 0x72, 0x10, d2_CurrentWindowId);
		rows[i].obj = list[i];
		*(int*) &((D2_WIN*)g_1015f40)[rows[i].text].pad280[12] = 0x56;
		*(int*) &((D2_WIN*)g_1015f40)[rows[i].text].pad14[4] = 0x10;
		t = gm_SearchTable67(*(int*) (rows[i].obj + 0xac));
		if (t != 0) {
			io_AppendText(0x1f41, t, *(int*) (rows[i].obj + 0xb4), *(int*) (rows[i].obj + 0xc0), rows[i].obj + 0xc4);
		}
	}
}
