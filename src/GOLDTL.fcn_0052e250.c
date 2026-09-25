// FUNCTION: GOLDTL 0x0052e250
// SIZE: 505

// SIZE 0x3cc
typedef struct {
	char pad0[0xc];
	int width;
	char pad10[0x3cc - 0x10];
} Slot;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int f5c;
	char pad60[0x2f4 - 0x60];
} Ent;

extern int g_6a25b8;
extern int g_1040494;
extern char g_6a2f40[];
extern char g_6a2f64[];
extern char g_6a2f24[];
extern char g_6a2f5c[];
extern unsigned char* g_7746c4;
extern unsigned char* g_7746c8;
extern int g_772514;
extern Slot g_1015f40[];
extern Ent* g_1015ea0;
extern char* g_99ec10;
extern unsigned short g_774970;
extern int g_14ad0d8;
extern int g_14ad0dc;
extern int g_6a25e0;
extern int g_6a25ec;

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_004727a0(int h, int mode);
void __cdecl fcn_00519190(char* fmt, ...);
int __cdecl fcn_0046f740(int x, int y, int kind, int owner);
unsigned short* __cdecl gm_ResolveParentEntity(unsigned short* e);
int __cdecl fcn_00506380(int id, unsigned char* store, int a, int b);
int __cdecl fcn_0050bf30(unsigned char* store, unsigned short* item, int a);
int __cdecl fcn_0052dee0(int x, int y, int z);

void __cdecl fcn_0052e250(unsigned short* item)
{
	unsigned char* store;
	unsigned short* parent;
	char* rec;
	int id;
	int fl;

	store = 0;
	if (g_6a25b8 != -1) {
		return;
	}
	if (*item >= 0x92 && *item <= 0x97) {
		return;
	}
	if (*item == 0x2db) {
		return;
	}
	g_6a25b8 = fcn_00470820(g_1040494 - 0x68, 0x106, g_6a2f40);
	fcn_004727a0(g_6a25b8, 1);
	if (g_7746c4 != 0 || g_7746c8 != 0) {
		store = g_7746c4 != 0 ? g_7746c4 : g_7746c8;
	}
	if (store != 0) {
		if (store[5] != 0) {
			fcn_00519190(g_6a2f64, *store * 14 + 0x48e, store + 5, *item * 2 + 0x9a8);
		} else {
			fcn_00519190(g_6a2f24, *store * 14 + 0x48e, *item * 2 + 0x9a8);
		}
	} else {
		fcn_00519190(g_6a2f5c, *item * 2 + 0x9a8);
	}
	fcn_004727a0(g_6a25b8, 0);
	id = fcn_0046f740(((g_1015f40[g_772514].width - 0x30) >> 1) - 1, 0x48, *item + 0xdf, g_772514);
	g_1015ea0[id].f5c = 1;
	rec = g_99ec10 + *item * 0x41;
	if (store != 0 && (*rec == 2 || *rec == 6)) {
		parent = gm_ResolveParentEntity(item);
		fl = fcn_00506380(g_774970, store, 0, 0);
		if (*parent != g_774970 && !(fl & 0x10)) {
			g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
		} else {
			if (fcn_0050bf30(store, item, 0)) {
				g_6a25ec = fcn_0052dee0(0, 0x8c, g_14ad0d8);
			}
			g_6a25e0 = fcn_0052dee0(0, 0xa6, g_14ad0dc);
		}
	}
}
