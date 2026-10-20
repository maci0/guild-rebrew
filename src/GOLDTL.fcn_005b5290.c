typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Rgb5b52;

// SIZE 0x1c
typedef struct {
	int type;
	char pad4[0x18];
} Cell5b52;

typedef struct {
	char pad0[0x20];
	int n;
	Cell5b52* cells;
	unsigned char* data;
} Map5b52;

extern int g_6b7fc0;
extern char g_6abaec[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_Plot(int, int, unsigned char, unsigned char, unsigned char);

void __cdecl fcn_005b5290(Map5b52* m, int x0, int y0, int x1, int y1)
{
	int frame;
	int h;
	Rgb5b52 pal[256];
	int x;
	int y;
	int c;
	int type;
	int v;
	int k;

	frame = 0;
	h = fcn_00470820(0, 0, g_6abaec);
	fcn_00471d80(h, 3);
	g_6b7fc0 = 1;
	*(int*) 0x6a2c04 = 0;
	while (fcn_005373e0((void*) fcn_005b5290, 0x277c7) != 0) {
		fcn_004727a0(h, 1);
		if (m != 0) {
			if (frame % 8 == 0) {
				for (c = 0; c < 256; c++) {
					pal[c].r = (unsigned char) c;
					pal[c].g = (unsigned char) c;
					pal[c].b = (unsigned char) c;
				}
				for (y = 0; y < m->n; y++) {
					for (x = 0; x < m->n; x++) {
						c = m->data[m->n * y + x];
						type = m->cells[m->n * y + x].type;
						if (type == 0 || type == 10 || type == 13) {
							v = pal[c].r + 0x20;
							if (v > 0xff) {
								v = 0xff;
							}
							d2_Plot(x, y, v, 0, (type == 13) ? 0xff : 0);
						}
						else if (type == 11 || type == 12) {
							v = pal[c].r + 0x20;
							if (v > 0xff) {
								v = 0xff;
							}
							d2_Plot(x, y, (type == 12) ? 0 : 0x60, v, 0);
						}
						else {
							d2_Plot(x, y, pal[c].r, pal[c].g, pal[c].b);
						}
					}
				}
				d2_Plot(x0, y0, 0xff, 0xff, 0xff);
				d2_Plot(x1, y1, 0xff, 0xff, 0xff);
			}
		}
		frame++;
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
	}
	fcn_00471e30(h);
	g_6b7fc0 = 0;
	*(int*) 0x6a2c04 = 1;
}
