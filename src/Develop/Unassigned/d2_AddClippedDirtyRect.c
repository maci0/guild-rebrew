typedef struct ClipRect {
	int x;
	int y;
	int w;
	int h;
} ClipRect;
// SIZE 0x10

#include "Develop/DieGildeAddOn/game/game_data.h"
extern ClipRect* g_77257c[2];
extern int g_77258c[2];

/* ADDRESS: GOLDTL 0x004660f0 */
void __cdecl d2_AddClippedDirtyRect(int x, int y, int w, int h)
{
	int i;
	int n;

	if (x & 1) {
		x--;
		w = (w + 2) & ~1;
	}
	if (y + h > d2_ClipBottom) {
		h = d2_ClipBottom - y;
	}
	if (y < g_7725fc) {
		h += y - g_7725fc;
		y = g_7725fc;
	}
	for (i = 0; i < 2; i++) {
		n = g_77258c[i];
		g_77257c[i][n].x = x;
		g_77257c[i][n].y = y;
		g_77257c[i][n].w = w;
		g_77257c[i][n].h = h;
		g_77258c[i]++;
	}
}
