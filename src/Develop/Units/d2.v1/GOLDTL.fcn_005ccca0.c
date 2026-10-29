extern unsigned short g_774970;
extern unsigned int g_775344;
extern int g_772514;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_14ce8e8;
extern int g_774654;
extern int g_6b7fac;
extern char* g_1015ea0;
extern char g_7f4ca0[];

/* Private layout views inferred from native accesses; they allocate no
 * storage and are visible only to this translation unit. */

// SIZE 0x38
typedef struct {
	void* ent;
	int key1;
	int key2;
	char pad0c[0x2c];
} SelRow_5ccca0;

// SIZE 0x14
typedef struct {
	int bild;
	int count;
	int element;
	int (__cdecl *create)(void*, int, void*, void*);
	void (__cdecl *present)(int, int, int, int, void*);
} TabRec_5ccca0;

extern TabRec_5ccca0 g_6ac8a8[];

int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00469110(int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005cc240(int, int, int);
void __cdecl fcn_005ccbe0(void);
void __cdecl fcn_005ccc00(int, int, void*);

/* ADDRESS: GOLDTL 0x005ccca0 */
int __cdecl fcn_005ccca0(void* ent, char* name, int tab, int callback, int dlg,
                         int unused)
{
	SelRow_5ccca0 rows[16];
	void* cur;
	int h;
	int i;
	int n;
	int old;
	int x;
	int y;
	int step;
	int rem;
	int state;
	int result;
	int time0;
	int sel;
	int win;

	time0 = g_6b7fac;
	sel = 0;
	fcn_005ccbe0();
	if (tab > -1 && tab < 8) {
		g_775344 = tab;
	}
	if (g_775344 >= 8) {
		g_775344 = 0;
	}
	win = g_772514;
	for (i = 0; i < 8; i++) {
		g_6ac8a8[i].count = g_6ac8a8[i].create(
				(char*) 0x7f4ca0 + g_774970 * 0x21c, 0, rows, ent);
	}
	if (g_6ac8a8[g_775344].count == 0) {
		g_775344 = 8;
		for (i = 0; i < 8; i++) {
			if (g_6ac8a8[i].count != 0) {
				g_775344 = i;
				break;
			}
		}
	}
	h = fcn_00470820(0, 0, "panel\\geb_liste");
	fcn_00471b60(h);
	d2_SetForm(h, 2);
	d2_SetForm(h, 1);
	fcn_00519190(name);
	d2_SetForm(h, 4);
	step = (*(int*) (0x1015f40 + g_772514 * 0x3cc + 0x10) - 0x107) / 7;
	rem = (*(int*) (0x1015f40 + g_772514 * 0x3cc + 0x10) - 0x107) % 7;
	y = 0;
	for (i = 0; i < 8; i++) {
		x = (*(int*) (0x1015f40 + g_772514 * 0x3cc + 0xc) - 0xb9) / 2;
		g_6ac8a8[i].element = fcn_00468df0(x, y, 0xbf,
				*(int*) (0x14aad40 + g_6ac8a8[i].bild * 4), g_772514);
		fcn_00469110(g_6ac8a8[i].element, 0xb9);
		y += 0x21 + step + (--rem >= 0);
	}
	if (g_775344 < 8) {
		d2_SetForm(h, 2);
		g_6ac8a8[g_775344].count = g_6ac8a8[g_775344].create(
				(char*) 0x7f4ca0 + g_774970 * 0x21c, 0x10, rows, ent);
		g_6ac8a8[g_775344].present(h, 2, 3, g_6ac8a8[g_775344].count, rows);
	}
	g_100f1dc = -1;
	state = 3;
	cur = (char*) 0x7f4ca0 + g_774970 * 0x21c;
	do {
		if (state == 3) {
			old = -1;
			if (g_775344 < 8) {
				old = g_6ac8a8[g_775344].count;
			} else {
				g_775344 = 0;
			}
			for (i = 0; i < 8; i++) {
				g_6ac8a8[i].count = g_6ac8a8[i].create(
						(char*) 0x7f4ca0 + g_774970 * 0x21c, 0, rows, ent);
			}
			if (g_6ac8a8[g_775344].count == 0) {
				g_775344 = 8;
				for (i = 0; i < 8; i++) {
					if (g_6ac8a8[i].count != 0) {
						g_775344 = i;
						break;
					}
				}
			}
			for (i = 0; i < 8; i++) {
				fcn_00472640(g_6ac8a8[i].element, g_6ac8a8[i].count != 0);
				*(int*) (g_1015ea0 + g_6ac8a8[i].element * 0x2f4 + 0x38) =
						i == g_775344;
			}
			if (g_775344 < 8) {
				n = g_6ac8a8[g_775344].create(
						(char*) 0x7f4ca0 + g_774970 * 0x21c, 0x10, rows, ent);
				g_6ac8a8[g_775344].count = n;
				g_6ac8a8[g_775344].present(state, 2, n != old ? 3 : -1, n, rows);
				fcn_005ccc00(state, g_6ac8a8[g_775344].count, rows);
			} else {
				fcn_005cc240(h, 2, 3);
				cur = (char*) 0x7f4ca0 + g_774970 * 0x21c;
			}
		} else if (state == 1) {
			i = g_6ac8a8[sel].create(
					(char*) 0x7f4ca0 + g_774970 * 0x21c, 0, 0, ent);
			g_6ac8a8[sel].count = i;
			if (i != 0) {
				*(int*) (g_1015ea0 + g_6ac8a8[g_775344].element * 0x2f4 + 0x38) = 0;
				g_775344 = sel;
				*(int*) (g_1015ea0 + g_6ac8a8[sel].element * 0x2f4 + 0x38) = 1;
				n = g_6ac8a8[g_775344].create(
						(char*) 0x7f4ca0 + g_774970 * 0x21c, 0x10, rows, ent);
				g_6ac8a8[g_775344].count = n;
				g_6ac8a8[g_775344].present(h, 2, 3, n, rows);
			} else {
				fcn_00472640(g_6ac8a8[sel].element, 0);
			}
		} else if (state == 4) {
			fcn_005ccc00(state, g_6ac8a8[g_775344].count, rows);
		} else if (state == 2) {
			time0 = 0;
		}
		result = 0;
		state = 0;
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_14ce8e8 != 0) {
			if (cur == (void*) ((char*) 0x7f4ca0 + g_774970 * 0x21c)) {
				n = g_6ac8a8[g_775344].count;
				if (n != 0) {
					for (i = 0; i < n; i++) {
						if (rows[i].key2 == g_67d370) {
							break;
						}
					}
					if (i > -1 && i < n) {
						if (rows[i].ent != 0 &&
								*(unsigned short*) rows[i].ent != 0xffff) {
							state = 4;
							cur = rows[i].ent;
						}
					}
				}
				goto after;
			}
			goto hit;
		} else {
			if (cur != (void*) ((char*) 0x7f4ca0 + g_774970 * 0x21c)) {
				state = 4;
				cur = (char*) 0x7f4ca0 + g_774970 * 0x21c;
			} else {
				goto hit;
			}
		}
		goto after;
	hit:
		if (g_100f1dc != -1) {
			for (i = 0; i < 8; i++) {
				if (g_6ac8a8[i].element == g_67d370) {
					state = 1;
					sel = i;
					goto after;
				}
			}
			n = g_6ac8a8[g_775344].count;
			if (n > 0) {
				for (i = 0; i < n; i++) {
					if (rows[i].key1 == g_67d370) {
						state = 2;
						sel = i;
						if (callback != 0) {
							fcn_00471af0(h, 0);
							if (((int (__cdecl*) (void*, int)) callback)(
										rows[i].ent, 0) != 0) {
								result = (int) rows[i].ent;
							} else {
								result = 0;
							}
							fcn_00471af0(h, 1);
						} else {
							result = (int) rows[i].ent;
							g_774654 = 1;
						}
					}
				}
			}
		} else if (time0 <= g_6b7fac &&
				*(int*) (0x1015f40 + win * 0x3cc + 0x260) == 0) {
			state = 3;
			time0 = g_6b7fac + 0xd8;
		}
	after:
		if (fcn_005373e0((void*) fcn_005ccca0, 0x657c7) == 0) {
			break;
		}
	} while (1);
	fcn_00471e30(h);
	return result;
}
