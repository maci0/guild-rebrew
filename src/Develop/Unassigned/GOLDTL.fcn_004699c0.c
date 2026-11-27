extern int g_772504,d2_ClipLeft,d2_ClipRight,g_7725fc,d2_ClipBottom,d2_DefaultFont,d2_ResourceOffset;
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_AllocateElement(void);
int __cdecl d2_ResolveResourceEntry(int, int*, int*);
void __cdecl d2_AddRefcount(int);
int __cdecl d2_AllocAnimationSlot(int, int, int, int);
int __cdecl fcn_0047b620(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x004699c0 */
int __cdecl d2_CreateElementCore(unsigned int x, int y, int resourceId)
{
	int v4;
	int n;
	int idx;

	char* slot;
	char* tp;
	int kind;
	int r;

	v4 = 0;
	if (resourceId > g_772504) {
		return -1;
	}
	idx = d2_AllocateElement();

	slot = (char*) &((D2_CONTROL_TL*)g_1015ea0)[idx];
	if (idx >= 0x400) {
		return -1;
	}
	d2_ResolveResourceEntry(resourceId, &v4, &n);
	*(int*) &((D2_CONTROL_TL*)slot)->data = v4;
	*(int*) &((D2_CONTROL_TL*)slot)->value_008 = n;
	*(int*) &((D2_CONTROL_TL*)slot)->kind = *(int*) (*(int*) &g_772500 + 0x3c + n * 0x54);
	*(int*) &((D2_CONTROL_TL*)slot)->x = x;
	*(int*) &((D2_CONTROL_TL*)slot)->y = y;
	*(int*) &((D2_CONTROL_TL*)slot)->clip_left = d2_ClipLeft;
	*(int*) &((D2_CONTROL_TL*)slot)->clip_right = d2_ClipRight;
	*(int*) &((D2_CONTROL_TL*)slot)->clip_top = g_7725fc;
	*(int*) &((D2_CONTROL_TL*)slot)->clip_bottom = d2_ClipBottom;
	*(int*) &((D2_CONTROL_TL*)slot)->mode = 2;
	*(int*) &((D2_CONTROL_TL*)slot)->font = d2_DefaultFont;
	d2_AddRefcount(n);
	kind = *(int*) &((D2_CONTROL_TL*)slot)->kind;
	if (kind == 8) {
		*(int*) &((D2_CONTROL_TL*)slot)->value_05c = 1;
	}
	*(int*) &((D2_CONTROL_TL*)slot)->value_1e4 = -1;
	*(int*) &((D2_CONTROL_TL*)slot)->value_1e8 = 0;
	*(int*) &((D2_CONTROL_TL*)slot)->value_1ec = 0;
	switch (kind) {
	case 1:
		tp = (char*) *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].data;
		*(int*) &((D2_CONTROL_TL*)slot)->width = *(unsigned short*) (tp + 6);
		*(int*) &((D2_CONTROL_TL*)slot)->height = *(unsigned short*) (tp + 8);
		return idx;
	case 4:
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].value_088 = d2_AllocAnimationSlot(x, y, *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].data, 0);
		tp = (char*) *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].data;
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].width = *(unsigned short*) (tp + 6);
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].height = *(unsigned short*) (tp + 8);
		return idx;
	case 17:
		tp = (char*) *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].data;
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].width = *(short*) (tp + 0xc);
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].height = *(short*) (tp + 0xe);
		*(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].value_088 = 2;
		return idx;
	case 5:
	case 8:
		*(int*) &((D2_CONTROL_TL*)slot)->value_088 = d2_ResourceOffset;
		tp = (char*) *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].data;
		r = fcn_0047b620((int) tp, *(int*) &((D2_CONTROL_TL*)g_1015ea0)[idx].value_088);
		*(int*) &((D2_CONTROL_TL*)slot)->width = *(unsigned short*) (r + 2);
		*(int*) &((D2_CONTROL_TL*)slot)->height = *(unsigned short*) (r + 6);
		*(int*) &((D2_CONTROL_TL*)slot)->value_1dc = -1;
		*(int*) &((D2_CONTROL_TL*)slot)->value_1e0 = -1;
		*(int*) &((D2_CONTROL_TL*)slot)->value_1d4 = *(unsigned short*) (tp + 6);
		*(int*) &((D2_CONTROL_TL*)slot)->value_1d8 = *(unsigned short*) (tp + 8);
		*(char*) &((D2_CONTROL_TL*)g_1015ea0)[idx].value_07c = 8;
		*(char*) &((D2_CONTROL_TL*)g_1015ea0)[idx].value_07d = 8;
		return idx;
	}
	return idx;
}
