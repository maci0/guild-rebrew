

#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct
{
	unsigned short* x0;
	char pad4[0xc];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	char pad30[8];
} Item;
// SIZE 0x38

extern int d2_CurrentWindowId;
extern Win_1015f40 g_1015f40[0x60];
extern int g_14aad98;
extern int g_14aad9c[];
extern char s_6a9680[];

int __cdecl d2_ClearAndScrollSubform(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowCenteredText(int, int, int, int, int);
void __cdecl d2_DrawPersonCard(int, int, int, int, Item*, int);
void __cdecl d2_CreateRightAlignedText(int, int, int, int, int);
void __cdecl d2_EnableDialogItems(unsigned int, Item*);

int __cdecl d2_LayoutTrialCandidateList(int dialogId, int formId, int altFormId, unsigned int n, Item* items)
{
	int y;
	char buf[0x100];
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = d2_ClearAndScrollSubform(dialogId, formId, altFormId);
	half = ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width / 2;
	io_FormatTextBuffer(buf, (int) s_6a9680, *items[0].x0);
	d2_ShowCenteredText((int) buf, half, 8, half * 2, 0x55);
	d2_ShowCenteredText(g_14aad98, half, 0x20, half * 2, 0x55);
	io_FormatTextBuffer(buf, (int) s_6a9680, *items[1].x0);
	d2_ShowCenteredText((int) buf, half, 0x38, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = 0x4b;
		items[i].x14 = i * 0x70 + 0x52;
		d2_DrawPersonCard(0x4b, i * 0x70 + 0x52, d2_CurrentWindowId, 0x56, &items[i], 1);
		d2_CreateRightAlignedText(g_14aad9c[items[i].x2c], 0x14a, i * 0x70 + 0x52 + 0x1e, 200, 0x55);
	}
	d2_EnableDialogItems(n, items);
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3c[0x21c] = y;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3c[0x238] = 0x70;
	return 1;
}
