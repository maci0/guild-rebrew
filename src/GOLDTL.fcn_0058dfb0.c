


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x1c4];
	unsigned char flags;
	char pad1cd[0x4f];
};

// SIZE 0x44
struct rec44 {
	int v[0x11];
};

// SIZE 0x58
struct result {
	int kind;
	int cost;
	int f8;
	unsigned char fc;
	char padd[3];
	int f10;
	struct rec44 rec;
};

extern char g_7f4ca0[];
extern unsigned short g_774970;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern int g_14b5650;
extern int g_14b5654;

void __cdecl fcn_005263d0(int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190();
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00525f60(struct house*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058dfb0(int a1, char* s, struct result* out)
{
	int b8;
	int price[3];
	int r;
	int h;
	int b4;
	int b6;
	int cancel;
	int k;
	struct rec44* p;

	r = 0;
	out->cost = 0;
	out->kind = 0;
	out->f8 = *(int*) (s + 0x20);
	out->fc = s[0x24];
	price[0] = 4;
	price[1] = 6;
	price[2] = 8;
	out->f10 = **(int**) (s + 0x2c + *(int*) (s + 0x88) * 0xc);
	p = *(struct rec44**) (s + 0x2c + *(int*) (s + 0x88) * 0xc);
	out->rec = *p;
	if ((((struct house*)g_7f4ca0)[g_774970].flags & 8) != 0) {
		fcn_005263d0(g_14b5650, g_14b5654, 0);
		return 0;
	}
	h = fcn_00470820(0, 0, "Locations\\Friedhof\\Seance");
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x40ce, 0x40cc);
	fcn_004727a0(h, 2);
	b4 = fcn_00472250(h, 2, fcn_00519190(0x40cf, 4));
	b6 = fcn_00472250(h, 2, fcn_00519190(0x40d0, 6));
	b8 = fcn_00472250(h, 2, fcn_00519190(0x40d1, 8));
	cancel = fcn_00472250(h, 2, fcn_00519190(0x40d2));
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == cancel) {
				g_774654 = 1;
			} else {
				if (g_67d370 == b4) {
					k = fcn_00525f60(&((struct house*)g_7f4ca0)[g_774970], 4);
				} else if (g_67d370 == b6) {
					k = fcn_00525f60(&((struct house*)g_7f4ca0)[g_774970], 6) * 2;
				} else if (g_67d370 == b8) {
					k = fcn_00525f60(&((struct house*)g_7f4ca0)[g_774970], 8) * 3;
				} else {
					continue;
				}
				if (k != 0) {
					out->kind = k;
					out->cost = price[k - 1];
					r = 1;
					g_774654 = 1;
				}
			}
		}
	} while (fcn_005373e0(fcn_0058dfb0, 0x677c7) != 0);
	fcn_00471e30(h);
	return r;
}
