

typedef struct Spin {
	char pad0[0x18];
	int max;
	int min;
	int pos;
	char pad24[0x28 - 0x24];
	unsigned char flags;
	char pad29[0x12c - 0x29];
	int value;
} Spin;
// SIZE 0x130

extern int tp_d2_SelectedControl;
extern int g_14ce8dc;
extern int g_14ce8d0;
extern int g_7725e8;
extern int d2_MouseTopBoundary;
extern int d2_MouseBottomBoundary;
extern int g_100f1e0;
extern int g_100f1d8;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_7725b8;
extern int g_7725dc;
extern int g_7725e0;

#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00473f50(Spin* p, int v, int a3, int a4);

int __cdecl fcn_00474780(void)
{
	int step;
	Spin* p;

	if ((*(Spin**)&tp_d2_SelectedControl) == 0 || !((*(Spin**)&tp_d2_SelectedControl)->flags & 2)) {
		return 0;
	}
	if (g_14ce8dc != 0 && (*(Spin**)&tp_d2_SelectedControl)->value < (*(Spin**)&tp_d2_SelectedControl)->max) {
		(*(Spin**)&tp_d2_SelectedControl)->value = (*(Spin**)&tp_d2_SelectedControl)->max;
	}
	if (g_14ce8d0 == 0 || (*(Spin**)&tp_d2_SelectedControl)->value == -1) {
		return 0;
	}
	if (g_7725e8 == 0) {
		step = d2_GetValueStep((char*) (*(Spin**)&tp_d2_SelectedControl));
		g_7725e8 = 1;
		g_100f1d8 = d2_MouseBottomBoundary;
		g_100f1e0 = d2_MouseTopBoundary;
		p = (*(Spin**)&tp_d2_SelectedControl);
		g_7725b8 = p->value;
		g_7725dc = g_14ce8c0;
		g_7725e0 = g_14ce8c2;
		if (p->flags & 0x80) {
			d2_MouseBottomBoundary = (g_7725b8 - p->min) * 4 / step + g_7725e0;
			d2_MouseTopBoundary = (g_7725b8 - p->max) * 4 / step + g_7725e0;
		}
		p->pos = (g_7725b8 - p->min) * 4 / step + g_7725e0;
	}
	fcn_00473f50((*(Spin**)&tp_d2_SelectedControl), g_7725b8, g_7725e0, g_14ce8c2);
	return 1;
}
