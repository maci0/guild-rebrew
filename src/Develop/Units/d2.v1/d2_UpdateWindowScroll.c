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
} D2_SCROLL_STEP_WIN;

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
} D2_SCROLL_STEP_ENT;

#include "Develop/client_types.h"

extern Win_1015f40 d2_Windows[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_PositionControl(int x, int y, int slot);

/* ADDRESS: GOLDTL 0x0046c310 */
/* ADDRESS: GOLDDE 0x0045f990 */
void __cdecl d2_UpdateWindowScroll(int win)
{
	D2_SCROLL_STEP_WIN* w;
	D2_SCROLL_STEP_ENT* ent;
	int v;
	int pos;
	int slot;
	int i;

	w = &((D2_SCROLL_STEP_WIN*)d2_Windows)[win];
	v = w->vx;
	if (v < 0) {
		w->x -= w->step;
		v = w->vx += w->step;
		if (v > 0) {
			w->vx = 0;
			w->x = v + w->x;
		}
		if (w->x >= 0) {
			goto y_axis;
		}
		w->x = 0;
	} else {
		if (v <= 0) {
			goto y_axis;
		}
		w->x += w->step;
		v = w->vx -= w->step;
		if (v < 0) {
			w->vx = 0;
			w->x = v + w->x;
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
		w->y -= w->step;
		v = w->vy += w->step;
		if (v > 0) {
			w->vy = 0;
			w->y = v + w->y;
		}
	} else if (v > 0) {
		w->y = w->y + w->step;
		w->vy = v - w->step;
	}
	if (w->x != w->prevx || w->y != w->prevy) {
		i = (w->type >> 3) & 1;
		if ((char)w->type & 0x20) {
			i += 2;
		}
		while (i < w->count) {
			slot = w->ids[i];
			ent = (D2_SCROLL_STEP_ENT*)&((D2_CONTROL_TL*)d2_Controls)[slot];
			d2_PositionControl(((*(int*)&((D2_CONTROL_TL*)ent)->x) - w->y) + w->prevy,
				((*(int*)&((D2_CONTROL_TL*)ent)->y) - w->x) + w->prevx, slot);
			if ((*(int*)&((D2_CONTROL_TL*)ent)->kind) == 0x11) {
				(*(int*)&((D2_CONTROL_TL*)ent)->value_088) = 2;
			}
			i++;
		}
	}
	w->prevx = w->x;
	w->prevy = w->y;
}
