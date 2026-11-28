

#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	char pad30[8];
} Item;
// SIZE 0x38

extern int d2_CurrentWindowId;
extern Win_1015f40 d2_Windows[0x60];
extern int g_14aadb0;
extern int g_14aadb4[];

int __cdecl d2_ClearAndScrollSubform(int, int, int);
void __cdecl d2_ShowCenteredText(int, int, int, int, int);
void __cdecl d2_DrawPersonCard(int, int, int, int, Item*, int);
void __cdecl d2_CreateRightAlignedText(int, int, int, int, int);
void __cdecl d2_EnableDialogItems(unsigned int, Item*);

int __cdecl d2_LayoutDuelOrPruegelCandidates(int dialogId, int formId, int altFormId, unsigned int n, Item* items)
{
	int y;
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = d2_ClearAndScrollSubform(dialogId, formId, altFormId);
	half = ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width / 2;
	d2_ShowCenteredText(g_14aadb0, half, 8, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = 0x4b;
		items[i].x14 = i * 0x70 + 0x28;
		d2_DrawPersonCard(0x4b, i * 0x70 + 0x28, d2_CurrentWindowId, 0x56, &items[i], 1);
		d2_CreateRightAlignedText(g_14aadb4[items[i].x2c], 0x14a, i * 0x70 + 0x28 + 0x1e, 200, 0x55);
	}
	d2_EnableDialogItems(n, items);
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x21c] = y;
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x238] = 0x70;
	return 1;
}
