

// SIZE 0x3
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Rgb5b4f;

// SIZE 0x1c
typedef struct {
	int type;
	char pad4[0x18];
} Cell5b4f;

typedef struct {
	char pad0[0x20];
	int n;
	Cell5b4f* cells;
	unsigned char* data;
} Map5b4f;

extern int g_67a370;
extern int g_7e46ac;
extern int g_100f1dc;
extern int g_67d370;
extern int g_14ce8e0;
extern int g_774654;
extern char g_6abad8[];
extern char g_6ababc[];
extern char g_6abaa8[];
extern char g_6aba94[];
extern char g_6aba80[];
extern char g_6aba70[];
extern char g_6aba5c[];
extern char g_6aba48[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471af0(int k, int flag);
void __cdecl fcn_005b3490(void);
void __cdecl fcn_005b3660(void);
void __cdecl fcn_005b37d0(void);
void __cdecl fcn_005b39c0(void);
void __cdecl fcn_005b3b60(void);
void __cdecl fcn_005b4500(void);
void __cdecl fcn_005b4c80(void);
void __cdecl d2_Plot(int, int, unsigned char, unsigned char, unsigned char);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005b4f70(void)
{
	int frame;
	int h5;
	int h6;
	int h2;
	int h7;
	int h4;
	int h3;
	int h1;
	Rgb5b4f pal[256];
	int t;
	int d;
	Map5b4f* m;
	int i;
	int x;
	int y;
	int type;
	int v;
	int c;
	int k;

	frame = 0;
	t = g_7e46ac;
	d = fcn_00470820(0, 0, g_6abad8);
	fcn_00471b60(d);
	fcn_004727a0(d, 0);
	h1 = fcn_00472250(d, 0, fcn_00519190(g_6ababc, 2));
	h2 = fcn_00472250(d, 0, fcn_00519190(g_6abaa8, 2));
	h3 = fcn_00472250(d, 0, fcn_00519190(g_6aba94, 2));
	h4 = fcn_00472250(d, 0, fcn_00519190(g_6aba80, 2));
	h5 = fcn_00472250(d, 0, fcn_00519190(g_6aba70, 2));
	h6 = fcn_00472250(d, 0, fcn_00519190(g_6aba5c, 2));
	h7 = fcn_00472250(d, 0, fcn_00519190(g_6aba48, 2));
	while (fcn_005373e0(fcn_005b4f70, t) != 0) {
		if (g_100f1dc != -1) {
			if (g_67d370 == h1) {
				fcn_005b3490();
			}
			if (g_67d370 == h2) {
				fcn_005b3660();
			}
			if (g_67d370 == h3) {
				fcn_005b37d0();
			}
			if (g_67d370 == h4) {
				fcn_005b39c0();
			}
			if (g_67d370 == h5) {
				fcn_00471af0(d, 0);
				fcn_005b3b60();
				fcn_00471af0(d, 1);
			}
			else if (g_67d370 == h6) {
				fcn_00471af0(d, 0);
				fcn_005b4500();
				fcn_00471af0(d, 1);
			}
			else if (g_67d370 == h7) {
				fcn_00471af0(d, 0);
				fcn_005b4c80();
				fcn_00471af0(d, 1);
			}
		}
		fcn_004727a0(d, 1);
		m = *(Map5b4f**) (((char*)g_67a370) + 0xb0);
		if (m != 0 && frame % 128 == 0) {
			for (i = 0; i < 256; i++) {
				pal[i].r = (unsigned char) i;
				pal[i].g = (unsigned char) i;
				pal[i].b = (unsigned char) i;
			}
			for (y = 0; y < m->n; y++) {
				for (x = 0; x < m->n; x++) {
					c = m->data[m->n * y + x];
					type = m->cells[m->n * y + x].type;
					if (type == 0 || type == 10 || type == 13) {
						v = pal[c].r + 0x20;
						if (v > 0xff) {
							k = 0xff;
						}
						else {
							k = v;
						}
						if (type != 13) {
							d2_Plot(x, y, k, 0, 0);
						}
						else {
							d2_Plot(x, y, k, 0, 0xff);
						}
					}
					else if (type == 11 || type == 12) {
						v = pal[c].r + 0x20;
						if (v > 0xff) {
							k = 0xff;
						}
						else {
							k = v;
						}
						if (type == 12) {
							d2_Plot(x, y, 0, k, 0);
						}
						else {
							d2_Plot(x, y, 0x60, k, 0);
						}
					}
					else {
						d2_Plot(x, y, pal[c].r, pal[c].g, pal[c].b);
					}
				}
			}
		}
		frame++;
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	fcn_00471e30(d);
}
