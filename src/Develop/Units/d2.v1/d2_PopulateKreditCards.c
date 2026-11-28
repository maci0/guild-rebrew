

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

extern char* d2_FileObjTable;
extern char* d2_CurrentWindow;
extern int d2_CurrentWindowId;
#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];

int __cdecl he_GetActiveKrediteByBorrower(int, int, char**);
void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_CreateChildWindow(int, int, int, int, int, int);
void* __cdecl gm_SearchTable67(int);
int __cdecl io_AppendText(int, ...);

void __cdecl d2_PopulateKreditCards(unsigned short* who, int max, Row* rows, int dlg, int n)
{
	char* list[9];
	int w;
	int i;
	int cnt;
	void* t;

	if (max >= 9) {
		max = 9;
	}
	cnt = he_GetActiveKrediteByBorrower(*who, 0, list);
	w = *(short*) (d2_FileObjTable + 0x269d8);
	if (cnt >= max) {
		cnt = max;
	}
	for (i = 0; i < cnt; i++) {
		d2_SetForm(dlg, n);
		rows[i].icon = d2_AddElementToWindow((((Screen*)d2_CurrentWindow)->width - w) >> 1, i * 0x80, 0x75a, d2_CurrentWindowId);
		rows[i].text = d2_CreateChildWindow((((Screen*)d2_CurrentWindow)->width - w) >> 1, i * 0x80 + 4, w, 0x72, 0x10, d2_CurrentWindowId);
		rows[i].obj = list[i];
		*(int*) &((D2_WIN*)d2_Windows)[rows[i].text].pad280[12] = 0x56;
		*(int*) &((D2_WIN*)d2_Windows)[rows[i].text].pad14[4] = 0x10;
		t = gm_SearchTable67(*(int*) (rows[i].obj + 0xac));
		if (t != 0) {
			io_AppendText(0x1f41, t, *(int*) (rows[i].obj + 0xb4), *(int*) (rows[i].obj + 0xc0), rows[i].obj + 0xc4);
		}
	}
}
