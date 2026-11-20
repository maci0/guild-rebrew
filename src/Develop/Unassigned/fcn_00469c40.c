#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_ScreenHeight;
extern int g_1040494;
#include "client_types.h"
extern Anim_100e7a0 g_100e7a0[0x30];
/* SIZE 0x2f4, g_1015ea0 entries */
typedef struct {
	char p00[0x10];
	int x10;
	int x14;
	int x18;
	int x1c;
	int x20;
	char p24[4];
	int x28;
	int x2c;
	int x30;
	int x34;
	char p38[8];
	int x40;
	char p44[0x38];
	unsigned char x7c;
	unsigned char x7d;
	char p7e[0xa];
	int x88;
	char p8c[0x268];
} Ent469c;

/* SIZE 0x3cc, g_1015f40 entries */
typedef struct {
	char p0[4];
	int x;
	int y;
	char p8[0x1c];
	int *ids;
	int n;
	char p30[0x3cc - 0x30];
} Win2_469;

/* child rect at Ent469c.x40 */
typedef struct {
	char p0[4];
	int x1;
	int y1;
	int x2;
	int y2;
} Rect469;









extern Win2_469 g_1015f40[0x60];
extern Fld_102d140 g_102d140[0x10];

/* ADDRESS: GOLDTL 0x00469c40 */
void __cdecl fcn_00469c40(int a1, int a2, int index)
{
	D2_CONTROL_TL *e;
	Rect469 *r;
	Win2_469 *w;
	int kind;
	int t;
	int i;
	int idx;
	int xo;
	int yo;

	e = (D2_CONTROL_TL *) g_1015ea0 + index;
	kind = e->kind;
	e->x = a1;
	e->y = a2;
	e->value_07c = 8;
	e->value_07d = 8;
	if (kind != 0x40) {
		e->clip_top = 0;
		e->clip_bottom = d2_ScreenHeight;
		e->clip_left = 0;
		e->clip_right = g_1040494;
	} else {
		e->clip_top = a2;
		e->clip_bottom = e->height + a2;
		e->clip_left = a1;
		e->clip_right = e->width + a1;
	}
	if ((*(int*)&e->parent) != 0) {
		r = (Rect469 *) (*(int*)&e->parent);
		t = (r->y1 > e->clip_top) ? r->y1 : e->clip_top;



		e->clip_top = t;
		t = (r->y2 + r->y1 < e->clip_bottom) ? r->y2 + r->y1 : e->clip_bottom;




		e->clip_bottom = t;
		if (t >= d2_ScreenHeight) {
			t = d2_ScreenHeight;
		}
		e->clip_bottom = t;
		t = (r->x1 > e->clip_left) ? r->x1 : e->clip_left;




		e->clip_left = t;
		t = (r->x1 + r->x2 < e->clip_right) ? r->x1 + r->x2 : e->clip_right;




		e->clip_right = t;
		if (t >= g_1040494) {
			t = g_1040494;
		}
		e->clip_right = t;
	}
	switch (kind) {
	case 4:
		*(unsigned short *) ((char*) g_100e7a0 + 0xe + e->value_088 * 20) = (unsigned short) e->x;
		*(unsigned short *) ((char*) g_100e7a0 + 0x10 + e->value_088 * 20) = (unsigned short) e->y;
		break;
	case 0x40:
		w = (Win2_469 *) g_1015f40 + e->value_088;
		xo = w->x;
		yo = w->y;
		w->x = a1;
		w->y = a2;
		if (e->clip_right > g_1040494) {
			e->clip_right = g_1040494;
		}
		if (e->clip_bottom > d2_ScreenHeight) {
			e->clip_bottom = d2_ScreenHeight;
		}
		for (i = 0; i < w->n; i++) {
			idx = w->ids[i];
			fcn_00469c40(((D2_CONTROL_TL *) g_1015ea0 + idx)->x - xo + w->x,
				     ((D2_CONTROL_TL *) g_1015ea0 + idx)->y - yo + w->y,
				     idx);
		}
		break;
	case 0x41:
		g_102d140[e->value_088].x = a1;
		g_102d140[e->value_088].y = e->y;
		break;
	}
}
