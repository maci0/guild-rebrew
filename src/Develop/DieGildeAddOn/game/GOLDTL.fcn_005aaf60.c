extern unsigned short g_774970;
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_772514;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern float g_662910;

int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_005c9030(int, int, int, int*);
int __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005aaf60 */
void __cdecl fcn_005aaf60(char* a0)
{
	char buf[480];
	int dlg;
	int h;
	int c;
	int a;
	int b;
	float total;
	float frac;
	int m;
	int n;
	int cnt;
	int v;
	int d;
	int i;
	int off;
	float scale;

	a = -1;
	b = -1;
	c = -1;
	if (a0 == 0) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) == g_774970) {
		return;
	}
	h = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0xe8);
	if (h == 0) {
		return;
	}
	m = gm_WalkEntityChain(g_774970);
	if (m <= 1) {
		m = 1;
	}
	n = gm_WalkEntityChain(*(unsigned short*) (a0 + 0x27));
	if (n <= 1) {
		n = 1;
	}
	total = (float) (m + n);
	cnt = (int) (total * g_662910);
	v = gm_AccumulateTyped2((char*) (g_774970 * 0x21c + (int) g_7f4ca0));
	dlg = fcn_00470820(0, 0, "Locations\\Kirche\\Spenden");
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 1);
	fcn_00519190(0x1986);
	if (v < cnt) {
		fcn_00519190(0x1987, g_774970,
			*(unsigned short*) ((unsigned char) g_773d75 * 0x2f4 + 0x8680b4) * 2 + 0x9a8);
	} else {
		c = fcn_00519190(0x1988, g_774970, *(unsigned short*) (a0 + 0x27), 0x48c,
			*(unsigned short*) ((unsigned char) g_773d75 * 0x2f4 + 0x8680b4) * 2 + 0x9a8);
		fcn_005c9030(cnt, v, 0x20, &b);
		c = fcn_00472250(dlg, 1, c);
		fcn_00472380(c, fcn_0050b710(cnt, g_773d75), fcn_0050b710(b, g_773d75),
			fcn_0050b710(cnt, g_773d75));
		d2_SetForm(dlg, 2);
		n = fcn_00519190(0x1989);
		a = fcn_00472250(dlg, 2, n);
		b = fcn_00472250(dlg, 2, n + 1);
	}
	*(int*) 0x100f1dc = -1;
	do {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc != -1) {
			if (*(int*) 0x67d370 == a) {
				d = fcn_0050b750(fcn_00471f80(c), g_773d75);
				if (fcn_00526010((char*) (g_774970 * 0x21c + (int) g_7f4ca0), d,
					g_773d75) != 0) {
					fcn_004c5150(*(int*) (h + 2), *(int*) (g_774970 * 0x21c + (int) g_7f4ca4),
						g_773d75, d);
					frac = (float) (d * 255) / total;
					fcn_004c54c0(*(int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + (int) g_7f4ca4),
						*(int*) (g_774970 * 0x21c + (int) g_7f4ca4), (int) frac, 1);
					scale = frac * *(float*) 0x6629d0;
					for (i = 0; i < 0x300; i++) {
						off = *(unsigned short*) (a0 + 0x27) * 0x21c;
						if (i == g_774970) {
							continue;
						}
						d = *(int*) (g_7f4ca4 + i * 0x21c);
						if (d == -1) {
							continue;
						}
						if (d == *(int*) (g_7f4ca4 + off)) {
							continue;
						}
						if (*(unsigned char*) (g_7f4ca4 + off + 8) !=
							*(unsigned char*) (g_7f4ca4 + i * 0x21c + 8)) {
							continue;
						}
						fcn_004c54c0(*(int*) (g_7f4ca4 + g_774970 * 0x21c), d, (int) scale, 1);
					}
					fcn_0051af00(buf, 0x67728c, 0x1986, 0x198a);
					fcn_00526120(buf, 0);
					*(int*) 0x774654 = 1;
				}
			} else if (*(int*) 0x67d370 == b) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005aaf60, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
