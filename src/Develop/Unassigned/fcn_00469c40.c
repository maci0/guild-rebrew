extern char *g_1015ea0;
extern int g_1040490;
extern int g_1040494;

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

/* SIZE 0x160, g_102d140 entries */
typedef struct {
	int idx;
	int x;
	int y;
	char pad[0x160 - 0xc];
} Fld_102d140;

extern Win2_469 g_1015f40[0x60];
extern Fld_102d140 g_102d140[0x10];

/* ADDRESS: GOLDTL 0x00469c40 */
void __cdecl fcn_00469c40(int a1, int a2, int a3)
{
	Ent469c *e;
	Rect469 *r;
	Win2_469 *w;
	int kind;
	int t;
	int i;
	int idx;
	int xo;
	int yo;

	e = (Ent469c *) g_1015ea0 + a3;
	kind = e->x20;
	e->x10 = a1;
	e->x14 = a2;
	e->x7c = 8;
	e->x7d = 8;
	if (kind != 0x40) {
		e->x30 = 0;
		e->x34 = g_1040490;
		e->x28 = 0;
		e->x2c = g_1040494;
	} else {
		e->x30 = a2;
		e->x34 = e->x1c + a2;
		e->x28 = a1;
		e->x2c = e->x18 + a1;
	}
	if (e->x40 != 0) {
		r = (Rect469 *) e->x40;
		t = r->y1;
		if (t <= e->x30) {
			t = e->x30;
		}
		e->x30 = t;
		t = r->y2 + r->y1;
		if (t >= e->x34) {
			t = e->x34;
		}
		e->x34 = t;
		if (t >= g_1040490) {
			t = g_1040490;
		}
		e->x34 = t;
		t = r->x1;
		if (t <= e->x28) {
			t = e->x28;
		}
		e->x28 = t;
		t = r->x1 + r->x2;
		if (t >= e->x2c) {
			t = e->x2c;
		}
		e->x2c = t;
		if (t >= g_1040494) {
			t = g_1040494;
		}
		e->x2c = t;
	}
	switch (kind) {
	case 4:
		*(unsigned short *) (0x100e7ae + e->x88 * 20) = (unsigned short) e->x10;
		*(unsigned short *) (0x100e7b0 + e->x88 * 20) = (unsigned short) e->x14;
		break;
	case 0x40:
		w = (Win2_469 *) g_1015f40 + e->x88;
		xo = w->x;
		yo = w->y;
		w->x = a1;
		w->y = a2;
		if (e->x2c > g_1040494) {
			e->x2c = g_1040494;
		}
		if (e->x34 > g_1040490) {
			e->x34 = g_1040490;
		}
		for (i = 0; i < w->n; i++) {
			idx = w->ids[i];
			fcn_00469c40(((Ent469c *) g_1015ea0 + idx)->x10 - xo + w->x,
				     ((Ent469c *) g_1015ea0 + idx)->x14 - yo + w->y,
				     idx);
		}
		break;
	case 0x41:
		g_102d140[e->x88].x = a1;
		g_102d140[e->x88].y = e->x14;
		break;
	}
}
