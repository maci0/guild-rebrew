typedef struct
{
	char pad0[0x14];
	int type;               /* 0x14 */
	char pad18[0x28 - 0x18];
	int* ids;               /* 0x28 */
	int count;              /* 0x2c */
	char pad30[0x254 - 0x30];
	int limit;              /* 0x254 */
	int x;                  /* 0x258 */
	int prevx;              /* 0x25c */
	int vx;                 /* 0x260 */
	int vy;                 /* 0x264 */
	int y;                  /* 0x268 */
	int prevy;              /* 0x26c */
	unsigned char step;     /* 0x270 */
	char pad271[0x3cc - 0x271];
} fcn_0046c310_Win;

typedef struct
{
	char pad0[0x10];
	int x;                  /* 0x10 */
	int y;                  /* 0x14 */
	char pad18[0x20 - 0x18];
	int kind;               /* 0x20 */
	char pad24[0x88 - 0x24];
	int anim;               /* 0x88 */
	char pad8c[0x2f4 - 0x8c];
} fcn_0046c310_Ent;

#include "client_types.h"

extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

void __cdecl fcn_00469c40(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x0046c310 */
void __cdecl fcn_0046c310(int win)
{
	fcn_0046c310_Win* w;
	fcn_0046c310_Ent* ent;
	int v;
	int pos;
	int slot;
	int i;

	w = &((fcn_0046c310_Win*)g_1015f40)[win];
	v = w->vx;
	if (v < 0) {
		v = v + w->step;
		pos = w->x - w->step;
		w->x = pos;
		w->vx = v;
		if (v > 0) {
			w->vx = 0;
			w->x = v + pos;
		}
		if (w->x >= 0) {
			goto y_axis;
		}
		w->x = 0;
	} else {
		if (v <= 0) {
			goto y_axis;
		}
		pos = w->x + w->step;
		v = v - w->step;
		w->x = pos;
		w->vx = v;
		if (v < 0) {
			w->vx = 0;
			w->x = v + pos;
		}
		if (w->x <= w->limit) {
			goto y_axis;
		}
		w->x = w->limit;
	}
	w->vx = 0;
y_axis:
	v = w->vy;
	if (v < 0) {
		v = v + w->step;
		pos = w->y - w->step;
		w->y = pos;
		w->vy = v;
		if (v > 0) {
			w->vy = 0;
			w->y = v + pos;
		}
	} else if (v > 0) {
		w->y = w->y + w->step;
		w->vy = v - w->step;
	}
	if (w->x != w->prevx || w->y != w->prevy) {
		i = ((char)w->type & 8) >> 3;
		if ((char)w->type & 0x20) {
			i += 2;
		}
		while (i < w->count) {
			slot = w->ids[i];
			ent = &((fcn_0046c310_Ent*)g_1015ea0)[slot];
			fcn_00469c40((ent->x - w->y) + w->prevy,
				(ent->y - w->x) + w->prevx, slot);
			if (ent->kind == 0x11) {
				ent->anim = 2;
			}
			i++;
		}
	}
	w->prevx = w->x;
	w->prevy = w->y;
}
