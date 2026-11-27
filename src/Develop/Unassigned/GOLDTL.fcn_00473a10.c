#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_7725c0;
extern char s_67d5ec[];

int __cdecl d2_FindResourceByName(const char* name);
char* __cdecl d2_GetResourceData(int idx);
void __cdecl d2_DrawCursorAndCounters(int a, int x, int y, int w, int h);

/* ADDRESS: GOLDTL 0x00473a10 */
int __cdecl d2_DrawMouseCursor(int x, int y)
{
	int px;
	int py;
	int a;
	int b;

	px = d2_MouseX + x;
	py = d2_MouseY + y;
	a = 6;
	b = 6;
	if (!g_7725c0) {
		g_7725c0 = d2_GetResourceData(d2_FindResourceByName(s_67d5ec));
	}
	if (g_14ce8d0) {
		px--;
		py++;
		a = 7;
		b = 5;
	}
	d2_DrawCursorAndCounters(g_77250c, px, py, a, b);
	return 1;
}
