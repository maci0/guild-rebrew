

#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x1c];
	int x34;
} Item;
// SIZE 0x38

#include "Develop/DieGildeAddOn/game/game_data.h"
extern Win_1015f40 d2_Windows[0x60];
extern int g_14aadc8;
#include "Develop/DieGildeAddOn/game/aemter.h"

int __cdecl d2_ClearAndScrollSubform(int, int, int);
void __cdecl d2_ShowCenteredText(int, int, int, int, int);
void __cdecl d2_DrawPersonCard(int, int, int, int, Item*, int);
void __cdecl d2_EnableDialogItems(unsigned int, Item*);

int __cdecl d2_LayoutOfficeCandidateList(int dialog, int selectedForm, int alternateForm, unsigned int n, Item* items)
{
	int y;
	int half;
	int pos;
	int cat;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = d2_ClearAndScrollSubform(dialog, selectedForm, alternateForm);
	half = ((D2_WIN*)d2_Windows)[d2_CurrentWindowId].width / 2;
	d2_ShowCenteredText(g_14aadc8, half, 8, half * 2, 0x55);
	pos = 0x28;
	cat = 0x28;
	for (i = 0; i < n; i++) {
		if (items[i].x34 != cat) {
			cat = items[i].x34;
			d2_ShowCenteredText((int) amt_OfficeNames[cat], half, pos, half * 2, 0x55);
			pos += 0x19;
		}
		items[i].x10 = 0x4b;
		items[i].x14 = pos;
		d2_DrawPersonCard(0x4b, pos, d2_CurrentWindowId, 0x56, &items[i], 1);
		pos += 0x70;
	}
	d2_EnableDialogItems(n, items);
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x21c] = y;
	*(int*) &((D2_WIN*)d2_Windows)[d2_CurrentWindowId].pad3c[0x238] = 0x70;
	return 1;
}
