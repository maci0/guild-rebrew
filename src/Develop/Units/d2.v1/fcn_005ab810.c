extern char g_7f4ca0[];
extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_772514;
extern int g_7f4c00;
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

/* Entity slot, stride 0x21c. */
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[4];
	unsigned char state;
	char pad_d[0x4f];
	int ref_table[8];
	char pad_7c[0x1a0];
};

int __cdecl gm_WalkEntityChain(unsigned short);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005ab810 */
void __cdecl fcn_005ab810(char* e, int unused)
{
	struct house* p;
	struct house* q;
	char* h;
	char* dlg;
	char buf[0x200];
	int t;
	int d;
	int x;
	int s;
	int v1;
	int v2;
	int i;

	p = &((struct house*) g_7f4ca0)[g_774970];
	t = (int) (gm_WalkEntityChain(g_774970) * 0.01f);
	if (e == 0) {
		return;
	}
	if (*(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (e + 0x27) == g_774970) {
		d = t * 15;
		dlg = fcn_00470820(0, 0, "Locations\\Kirche\\Taufe");
		fcn_00473a90(0, 0);
		fcn_00471b60((int) dlg);
		d2_SetForm((int) dlg, 0);
		fcn_005340f0(g_772514);
		d2_SetForm((int) dlg, 1);
		fcn_00519190(0x1976, p->id, d, 2 * (0x75 <= g_7f4c00) + 0x197a + 1 - p->state);
		d2_SetForm((int) dlg, 2);
		s = fcn_00519190(0x1977);
		v1 = fcn_00472250((int) dlg, 2, s);
		v2 = fcn_00472250((int) dlg, 2, s + 1);
		g_100f1dc = -1;
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (g_67d370 == v1) {
					if (fcn_00526010(&((struct house*) g_7f4ca0)[g_774970], d, (char) g_773d75) != 0) {
						x = 1 - p->state;
						fcn_004c51a0(-1, p->handle, 0, d);
						fcn_004c4510((char*) p, p->handle);
						fcn_004c4570(1, 1, 0xc, &x);
						fcn_004c5360();
						for (i = 3; i <= 7; i++) {
							h = (char*) p->ref_table[i];
							if (h != (char*) -1) {
								h = (char*) fcn_00508e40((int) h);
								if (h != 0) {
									fcn_004c4510(h, *(int*) (h + 4));
									fcn_004c4570(1, 1, 0xc, &x);
									fcn_004c5360();
								}
							}
						}
						fcn_0051af00(buf, 0x1978, p->id, e, 2 * (0x75 <= g_7f4c00) + 0x197a + x);
						for (i = 0x7f4ca4; i < 0x85a0a4; i += 0x21c) {
							if (*(int*) i != p->handle && (*(char*) (i - 2) == 6 || *(char*) (i - 2) == 7)) {
								fcn_00545d40(*(int*) i, -1, buf, 0, 0x5fe, 0);
							}
						}
						fcn_0051af00(buf, 0x1979, 2 * (0x75 <= g_7f4c00) + 0x197a + x);
						fcn_00526120(buf, 0);
						g_774654 = 1;
					}
				} else if (g_67d370 == v2) {
					g_774654 = 1;
				}
			}
		} while (fcn_005373e0((void*) 0x5ab810, 0x677c7) != 0);
		fcn_00471e30((int) dlg);
	} else {
		q = &((struct house*) g_7f4ca0)[*(unsigned short*) (e + 0x27)];
		if (q == 0) {
			return;
		}
		if (q->state == p->state) {
			fcn_0051af00(buf, 0x1970);
			fcn_00526120(buf, 0);
			return;
		}
		dlg = fcn_00470820(0, 0, "Locations\\Kirche\\Taufe");
		fcn_00473a90(0, 0);
		fcn_00471b60((int) dlg);
		d2_SetForm((int) dlg, 0);
		fcn_005340f0(g_772514);
		d2_SetForm((int) dlg, 1);
		fcn_00519190(0x1971, p->id, t, 2 * (0x75 <= g_7f4c00) + 0x197a + q->state);
		d2_SetForm((int) dlg, 2);
		s = fcn_00519190(0x1972);
		v1 = fcn_00472250((int) dlg, 2, s);
		v2 = fcn_00472250((int) dlg, 2, s + 1);
		g_100f1dc = -1;
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (g_67d370 == v1) {
					if (fcn_00526010(&((struct house*) g_7f4ca0)[g_774970], t, (char) g_773d75) != 0) {
						x = q->state;
						fcn_004c51a0(q->handle, p->handle, 0, t);
						fcn_004c4510((char*) p, p->handle);
						fcn_004c4570(1, 1, 0xc, &x);
						fcn_004c5360();
						if (q->type == 6 || q->type == 7) {
							fcn_0051af00(buf, 0x1974, p->id, t, 2 * (0x75 <= g_7f4c00) + 0x197a + x);
							fcn_00545d40(q->handle, -1, buf, 0, 0x5ff, 0);
						}
						fcn_0051af00(buf, 0x1973, 2 * (0x75 <= g_7f4c00) + 0x197a + x);
						fcn_00526120(buf, 0);
						g_774654 = 1;
					}
				} else if (g_67d370 == v2) {
					g_774654 = 1;
				}
			}
		} while (fcn_005373e0((void*) 0x5ab810, 0x677c7) != 0);
		fcn_00471e30((int) dlg);
	}
	fcn_00532ef0();
}
