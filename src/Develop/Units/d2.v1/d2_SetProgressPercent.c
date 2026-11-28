extern int g_7e1d40;




void __cdecl d2_SetForm(int, int);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_RenderAndPresentFrame(void);

/* ADDRESS: GOLDDE 0x00526140 */
void __cdecl d2_SetProgressPercent(int a, int pct)
{
	int t;

	if (g_7e1d40 != -1) {
		d2_SetForm(g_7e1d40, 0);
		d2_SetForm(g_7e1d40, 1);
		t = d2_GetWindowListItem(g_7e1d40, 1, 0);
		d2_SetElementValue(t, 0, 0x246, pct * 0x246 / 100);
		d2_RenderAndPresentFrame();
	}
}
