

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	char pad0[0x5c];
	int x5c;
	char pad60[0x170];
	int x1d0;
	char pad1d4[0x11c];
	char* x2f0;
} Slot;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int d2_CurrentWindowId;
extern char s_6ac948[];
extern char s_68be7c[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CalculateGebaeudeValue(char*, int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_PopulateOwnerBuildingList(unsigned short* who, int n, int* arr)
{
	int cnt;
	int flag;
	char buf[0x100];
	int y;
	char* e;
	int v;
	int h;

	y = 0;
	flag = 0;
	if (n > 0 && arr != 0) {
		flag = 1;
		memset(arr, 0xff, n * 4);
	}
	h = 0;
	cnt = 0;
	for (e = gm_StartFilteredEntitySearch(1, 4, *who); e != 0; e = gm_FindNextFilteredEntity()) {
		if (e[0x5a] & 1) {
			continue;
		}
		v = gm_CalculateGebaeudeValue(e, e[0x5c]);
		h = d2_AddElementToWindow(0x20, y, (unsigned char) e[0] + 0x427, d2_CurrentWindowId);
		io_FormatTextBuffer(buf, s_6ac948, e);
		d2_ShowTxt(0x80, y, buf, d2_CurrentWindowId);
		io_FormatTextBuffer(buf, s_68be7c, v);
		d2_ShowTxt(0x80, y + 0x1b, buf, d2_CurrentWindowId);
		if (flag == 1 && cnt < n) {
			((D2_CONTROL_TL*) g_1015ea0)[h].value_05c = 1;
			((D2_CONTROL_TL*) g_1015ea0)[h].flags_1d0 = 3;
			((D2_CONTROL_TL*) g_1015ea0)[h].associated_object = e;
			arr[cnt] = h;
		}
		cnt++;
		y += 0x40;
	}
	return cnt;
}
