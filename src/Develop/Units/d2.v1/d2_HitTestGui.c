typedef struct Slot {
	int id;
	int used;
	int value;
	int pad0c;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x28 - 0x24];
	int left;
	int right;
	int top;
	int bottom;
	char pad38[0x40 - 0x38];
	int* link;
	int pad44;
	int hidden48;
	int hidden4c;
	char* owner;
	char pad54[0x58 - 0x54];
	int f58;
	int f5c;
	int pad60;
	int f64;
	char pad68[0x88 - 0x68];
	int result;
	char pad8c[0x1d0 - 0x8c];
	unsigned char flags1d0;
	char pad1d1[0x2f4 - 0x1d1];
} Slot;
// SIZE 0x2f4

#include "Develop/Units/d2.v1/d2_win.h"





// SIZE 0x3cc

extern char* g_1015ea0;
#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern void** g_772540;
extern int g_67d38c;
extern int g_67d388;
extern int g_67d374;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_HitTestWindow(int x, int y);
int __cdecl d2_HitTestRenderableForm(int x, int y);

/* ADDRESS: GOLDTL 0x0046aee0 */
int __cdecl d2_HitTestGui(int x, int y)
{
	int i;
	int hidden;
	Slot* s;
	Slot* w;
	int* lk;
	int left;
	int right;
	int top;
	int bottom;
	int r;

	d2_HitTestWindow(x, y);
	g_67d38c = -1;
	g_67d374 = -1;
	for (i = 0x3ff; i >= 0; i--) {
		hidden = 0;
		s = ((Slot**)g_772540)[i];
		if (s) {
			if (s->owner) {
				hidden = *(int*) (s->owner + 0x198);
			}
			if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && !hidden
				&& y >= s->top && y <= s->bottom && !s->hidden4c && !s->hidden48 && ((Slot*)g_1015ea0)[s->id].type == 0x40 && *(int*) &((D2_WIN*)g_1015f40)[s->result].pad3c[0x238]) {
				g_67d38c = s->result;
				break;
			}
		}
	}
	for (i = 0x3ff; i >= 0; i--) {
		hidden = 0;
		s = ((Slot**)g_772540)[i];
		if (s) {
			if (s->owner) {
				hidden = *(int*) (s->owner + 0x198);
			}
			if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && !hidden) {
				lk = s->link;
				if (lk) {
					w = &((Slot*)g_1015ea0)[lk[0x27c / 4]];
					left = lk[1] > w->left ? lk[1] : w->left;
					right = lk[1] + lk[3] < w->right ? lk[1] + lk[3] : w->right;
					top = lk[2] > w->top ? lk[2] : w->top;
					bottom = lk[2] + lk[4] < w->bottom ? lk[2] + lk[4] : w->bottom;
				} else {
					left = s->left;
					right = s->right;
					top = s->top;
					bottom = s->bottom;
				}
				if (y >= top && y <= bottom && x >= left && x <= right && !s->hidden48 && (s->f5c || s->f58 || s->type == 0x41 || s->f64)) {
					if (!s->hidden4c) {
						g_67d374 = d2_CurrentElementId = s->id;
						if (s->link) {
							g_67d388 = *s->link;
						}
						if (s->type == 9) {
							return (s->flags1d0 & 0x10) ? 1 : 2;
						}
						return s->value;
					}
					if (g_67d374 == -1) {
						g_67d374 = s->id;
					}
					d2_CurrentElementId = -1;
				}
			}
		}
	}
	r = d2_HitTestRenderableForm(x, y);
	if (r == -1) {
		d2_CurrentElementId = -1;
		r = -1;
	}
	return r;
}
