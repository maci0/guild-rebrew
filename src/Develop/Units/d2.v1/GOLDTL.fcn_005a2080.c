extern int g_772514;
extern char* g_772500;
extern char* g_77255c;
extern unsigned short g_774970;
extern int g_774654;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern char g_6b5c60[];
extern char g_6811b0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl d2_SetOverlayAnimation(int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl fcn_00502cd0(int, ...);
int __cdecl fcn_0046f2c0(int, int);
int __cdecl io_AppendText(char* fmt, ...);
int __cdecl fcn_005ca560(void*);
void __cdecl fcn_005ca740(int, int, int, int, void*, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c6900(int*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl io_FormatTextBuffer(char*, int, int);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005a2080 */
void __cdecl fcn_005a2080(int a0, int a1)
{
	int sel[4][0xe];
	char buf[0x200];
	int join[3];
	int win;
	int next;
	int i;
	int n;
	int found;
	int state;
	int changed;
	int x0;
	int y0;
	int *p;
	int *q;
	unsigned int *ip;
	unsigned short* ent;

	for (i = 0; i < 4; i++) {
		for (n = 0; n < 0xe; n++) {
			sel[i][n] = 0;
		}
	}
	win = fcn_00470820(0, 0, "locations\\Wirtshaus\\Stammtisch");
	fcn_00471b60(win);
	d2_SetForm(win, 0);
	fcn_005340f0(g_772514);
	d2_SetOverlayAnimation(0, 0);
	ip = (unsigned int*) (a1 + 0x1c);
	for (;;) {
		i = 0;
		n = 0;
		state = 0;
		changed = 0;
		p = sel[0];
		q = (int*) ip;
		for (i = 0; i < 4; i++) {
			ent = (unsigned short*) gm_LookupEntityRecordById(*ip);
			if ((int) ent != p[0]) {
				changed = 1;
			}
			if (ent != 0) {
				p[0] = (int) ent;
				n++;
				p += 0xe;
				if (*(int*) (ent + 2) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) {
					state = 1;
				}
			}
			ip++;
		}
		if (n != 4) {
			if (n <= 3) {
				if (state == 0) {
					state = 3;
					next = (int) gm_StartFilteredEntitySearch(1, 0, 0x37);
					while (next != 0) {
						next = (int) fcn_00502cd0(*(int*) (next + 0x5d), 2, 6, 0, 0x12d);
						if (next != 0) {
							i = 0;
							p = (int*) (next + 0x1c);
							do {
								if (*p == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) {
									state = 4;
									break;
								}
								i++;
								p++;
							} while (i < 4);
						}
						next = (int) gm_FindNextFilteredEntity();
					}
				}
				for (i = n; i < 4; i++) {
					sel[i][0] = 0;
				}
			}
		} else if (state == 0) {
			state = 2;
		}
		if (changed) {
			d2_SetForm(win, 1);
			fcn_0046f2c0(g_772514, 1);
			io_AppendText((char*) 0x188c, a0);
			if (n != 0) {
				x0 = *(int*) (g_77255c + 0xc) + *(short*) (g_772500 + 0x1ebd8) * -2;
				p = sel[0];
				for (i = 0; i < n; i++) {
					p[0xc] = 1;
					p[4] = (i & 1) * (x0 / 3) + -10 + (x0 % 3) / 2 + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i & 1);
					p[5] = (i / 2) * 0x82 + 100;
					fcn_005ca560(p);
					fcn_005ca740(p[4], p[5], g_772514, 0x54, p, 1);
					p += 0xe;
				}
			} else {
				io_AppendText((char*) 0x188e);
			}
			d2_SetForm(win, 2);
			fcn_0046f2c0(g_772514, 1);
			io_AppendText(g_6811b0);
			win = -1;
			if (state != 2) {
				if (state != 4) {
					if (state != 3) {
						if (state != 1) {
							goto label_5a23ad;
						}
						i = 0x1890;
					} else {
						i = 0x188f;
					}
					win = fcn_00472250(io_AppendText((char*) i), 2, 0);
				} else {
					io_AppendText((char*) 0x1891);
				}
			} else {
				io_AppendText((char*) 0x1892);
			}
		}
label_5a23ad:
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1 && g_67d370 == win && state == 3) {
			buf[0] = g_6b5c60[0];
			for (i = 0; i < 0x7f; i++) {
				buf[i] = 0;
			}
			buf[0x1fc] = 0;
			if (g_100f1dc == 2) {
				join[0] = 0x6a6f696e;
				join[1] = *(int*) (a0 + 1);
				join[2] = *(int*) (g_774970 * 0x21c + 0x7f4ca4);
				fcn_004c4eb0("stammtisch join H-Plr");
				fcn_004c6900(join);
				fcn_004c4ef0("stammtisch join H-Plr");
				n = fcn_004c4450((int) join);
				while (n == 0) {
					fcn_005373e0(0, 0x20007);
					n = fcn_004c4450((int) join);
				}
				io_FormatTextBuffer(buf, (n != 1) ? 0x189f : 0x189e, a0);
			}
			if (buf[0] != 0) {
				fcn_00526120(buf, 0);
			}
		}
		if (!fcn_005373e0((void*) 0x5a1e40, 0x677c7)) {
			fcn_00471e30(win);
			return;
		}
	}
}
