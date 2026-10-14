

// SIZE 0x21c
typedef struct {
	unsigned short id;
	char pad2[0x166];
	unsigned char owner;
	char pad169[0xb3];
} House5a96;

// SIZE 0x38
typedef struct {
	House5a96* house;
	char pad4[0xc];
	int x;
	int y;
	char pad18[0x18];
	int f30;
	int pad34;
} Item5a96;

#define HOUSES 768

extern char g_7f4ca0[];
extern char* g_772500;
extern char* g_77255c;
extern int g_772514;
extern int g_14abb40;
extern int g_14abb44;
extern int g_14abb48;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6aae98[];

int __cdecl fcn_004e8a80(int, void*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190();
void __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_0046f2c0(int, int);
int __cdecl fcn_005ca560(Item5a96* s);
void __cdecl fcn_005ca740(int, int, int, int, Item5a96*, int);
void __cdecl fcn_00472640(int i, int flag);
int __cdecl fcn_004e7d40(char*, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_004e6f10(int a);
void __cdecl fcn_005cadc0(int, int, int, int, void*);
void __cdecl fcn_0052f7a0(void);
void __cdecl fcn_005cdd90(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005a96a0(char* who, int id)
{
	int d;
	int ha;
	int res;
	int hc;
	int hb;
	int prev;
	int w;
	int ids[3];
	House5a96* houses[4];
	char info[0x18];
	Item5a96 items[4];
	int n;
	int j;
	int i;
	int off;
	int r;

	res = 0;
	d = -1;
	ha = -1;
	hb = -1;
	hc = -1;
	prev = -1;
	g_100f1dc = -1;
	do {
		if (fcn_004e8a80(id, info) == 0) {
			g_774654 = 1;
		}
		else {
			n = 0;
			for (j = 0; j < HOUSES; j++) {
				if (n >= 4) {
					break;
				}
				if (((House5a96*)g_7f4ca0)[j].id != 0xffff && ((House5a96*)g_7f4ca0)[j].owner == id) {
					houses[n] = &((House5a96*)g_7f4ca0)[j];
					n++;
				}
			}
			if (prev != n) {
				prev = n;
				if (d == -1) {
					d = fcn_00470820(0, 0, g_6aae98);
					fcn_00471b60(d);
					fcn_00473a90(0, 0);
					fcn_004727a0(d, 1);
					fcn_00519190(0x1a07, id + 0x253);
					fcn_004727a0(d, 3);
					fcn_00533a60(g_772514, 0, ids, 3, g_14abb40, g_14abb44, g_14abb48);
					ha = ids[0];
					hb = ids[1];
					hc = ids[2];
				}
				fcn_004727a0(d, 2);
				fcn_0046f2c0(g_772514, 1);
				fcn_00519190(0x1a0b);
				if (n <= 0) {
					fcn_00519190(0x1a0c);
				}
				else {
					w = (((int*)g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 2) / 3;
					off = (((int*)g_77255c)[3] - *(short*) (g_772500 + 0x1ebd8) * 2) % 3 / 2;
					for (i = 0; i < n; i++) {
						items[i].x = off + (*(short*) (g_772500 + 0x1ebd8) + 10) * (i % 2) + (i % 2 + 1) * w - 10;
						items[i].f30 = 0;
						items[i].y = i / 2 * 0x41 * 2 + 0x28;
						items[i].house = houses[i];
						fcn_005ca560(&items[i]);
						fcn_005ca740(items[i].x, items[i].y, g_772514, 0x56, &items[i], 1);
					}
				}
				if (n < 4 && who[0x168] == 0) {
					fcn_00472640(ha, 1);
				}
				else {
					fcn_00472640(ha, 0);
				}
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		else if (g_100f1dc != -1) {
			if (g_67d370 == ha) {
				r = fcn_004e7d40(who, id);
				if (r != -1) {
					do {
						if (fcn_004c4450(r) != 0) {
							break;
						}
						fcn_00535960();
					} while (1);
				}
				if (fcn_004c4450(r) == 1) {
					res = 1;
				}
				fcn_0057e880(0x2f, 0, 0, id);
			}
			else if (g_67d370 == hb) {
				r = fcn_004e6f10(id);
				fcn_005cadc0(r, 0, 0, 0, fcn_0052f7a0);
			}
			else if (g_67d370 == hc) {
				fcn_005cdd90(id, 0);
			}
		}
	} while (fcn_005373e0(fcn_005a96a0, 0x677c7) != 0);
	if (d != -1) {
		fcn_00471e30(d);
	}
	if (res != 0) {
		g_774654 = 1;
		fcn_0057e880(0x2f, 0, 1, id);
	}
	return res;
}
