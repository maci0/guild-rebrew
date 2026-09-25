/* GOLD twin of GOLDTL fcn_00467480. GOLD's window and entity records keep
 * their coordinates and the child count as shorts (window 0x3c4 bytes, entity
 * 0x2ec) where GOLDTL uses ints (0x3cc, 0x2f4). */

// SIZE 0x3c4
typedef struct Win_46a350 {
	int a0;
	short x;
	short y;
	short w;
	short h;
	char pad0c[0x12 - 0xc];
	short f12;
	char pad14[0x18 - 0x14];
	int* list;
	short count;
	char pad1e[0x248 - 0x1e];
	int scroll;
	char pad24c[0x26c - 0x24c];
	int parent;
	char pad270[0x27c - 0x270];
	short f27c;
	short pad27e;
	int active;
	char pad284[0x3c4 - 0x284];
} Win_46a350;

// SIZE 0x2ec
typedef struct Ent_46a350 {
	char pad0[0x10];
	short f10;
	char pad12[0x1e - 0x12];
	short left;
	short right;
	short top;
	short bottom;
	char pad26[0x30 - 0x26];
	Win_46a350* win;
	int pad34;
	int f38;
	int pad3c;
	int f40;
	char pad44[0x78 - 0x44];
	int fld;
	char pad7c[0x2ec - 0x7c];
} Ent_46a350;

// SIZE 0x160
typedef struct Fld_46a350 {
	int f0;
	char pad4[0x24 - 4];
	int f24;
	char pad28[0x160 - 0x28];
} Fld_46a350;

extern Win_46a350 g_f8f120[];
extern Ent_46a350* g_f8f080;
extern Fld_46a350 g_fa6158[];
extern char s_5fe7ac[];

void __cdecl fcn_004222b0(const char* msg);
int __cdecl fcn_0046a100(int x, int y, int a3, int a4, int a5);
void __cdecl fcn_004730d0(int slot, Win_46a350* parent);

// FUNCTION: GOLD 0x46a350
// SIZE: 350
int __cdecl fcn_0046a350(int x, int y, int a3, int a4, int a5, int win)
{
	Win_46a350* w;
	int id;

	w = &g_f8f120[win];
	if (w->active == 0) {
		return -1;
	}
	if (w->count >= 0x180) {
		fcn_004222b0(s_5fe7ac);
		return -1;
	}
	id = fcn_0046a100(w->x + x, w->y - w->scroll + y, a3, a4, a5);
	fcn_004730d0(id, w);
	g_f8f080[id].win = w;
	g_f8f080[id].f40 = g_f8f080[w->parent].f40;
	g_f8f080[id].top = w->y;
	g_f8f080[id].bottom = w->h + w->y;
	g_f8f080[id].left = w->x;
	g_f8f080[id].right = w->x + w->w;
	g_fa6158[g_f8f080[id].fld].f0 = w->f27c;
	g_fa6158[g_f8f080[id].fld].f24 = w->x - g_f8f080[id].f10 - w->f12 + w->w;
	w->list[w->count] = id;
	w->count++;
	return id;
}
