

#include "Develop/Units/d2.v1/gold_window.h"









// SIZE 0x3c4

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	char pad30[4];
	int x34;
} Item;
// SIZE 0x38

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_types.h"
extern int g_14aadc0[];

int __cdecl fcn_005cc240(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005c9160(int, int, int, int, int);
void __cdecl d2_EnableDialogItems(unsigned int, Item*);

int __cdecl d2_LayoutScrolledItemDialog(int dialogId, int formId, int altFormId, unsigned int n, Item* items)
{
	int y;
	char buf[0x200];
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = fcn_005cc240(dialogId, formId, altFormId);
	half = g_f8f120[d2_CurrentWindowId].width / 2;
	io_FormatTextBuffer(buf, 0x16a7, items[0].x34 + 0x253);
	fcn_005c9090((int) buf, half, 8, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = 0x4b;
		items[i].x14 = i * 0x70 + 0x28;
		fcn_005ca740(0x4b, i * 0x70 + 0x28, d2_CurrentWindowId, 0x56, &items[i], 1);
		fcn_005c9160(g_14aadc0[items[i].x2c], 0x14a, i * 0x70 + 0x28 + 0x1e, 200, 0x55);
	}
	d2_EnableDialogItems(n, items);
	g_f8f120[d2_CurrentWindowId].scroll = y;
	g_f8f120[d2_CurrentWindowId].step = 0x70;
	return 1;
}
