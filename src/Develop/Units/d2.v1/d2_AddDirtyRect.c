typedef struct DirtyRect {
	int x;
	int y;
	void* owner;
	int w;
	int h;
} DirtyRect;
// SIZE 0x14

#include "Develop/DieGildeAddOn/game/game_data.h"
extern DirtyRect* d2_DirtyRects;

/* ADDRESS: GOLDTL 0x00465ff0 */
void __cdecl d2_AddDirtyRect(int x, int y, int w, int h, char* owner)
{
	int i;

	if (*(int*) (owner + 0x190) == 0 || owner + 0x1ac == 0) {
		return;
	}
	if (x > d2_ClipRight) {
		x = d2_ClipRight;
	}
	if (x & 1) {
		x--;
		w = (w + 2) & ~1;
	}
	if (y + h > d2_ClipBottom) {
		h = d2_ClipBottom - y;
	}
	if (x + w > d2_ClipRight) {
		w = d2_ClipRight - x;
	}
	if (y < g_7725fc) {
		y = g_7725fc;
	}
	if (x < d2_ClipLeft) {
		x = d2_ClipLeft;
	}
	if (w < 0) {
		w = 1;
	}
	if (h < 0) {
		h = 1;
	}
	for (i = 0; d2_DirtyRects[i].owner != 0 && i < 0x400; i++) {
	}
	if (i < 0x400) {
		d2_DirtyRects[i].x = x;
		d2_DirtyRects[i].y = y;
		d2_DirtyRects[i].w = w;
		d2_DirtyRects[i].h = h;
		d2_DirtyRects[i].owner = owner;
	}
}
