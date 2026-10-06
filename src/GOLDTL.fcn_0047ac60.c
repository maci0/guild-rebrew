typedef struct Item {
	char pad0[0x48];
	int refs;
	int size;
} Item;
// SIZE 0x50

typedef struct Group {
	char pad0[0x24];
	int count;
	Item** items;
	int pad2c;
	void* extra;
} Group;
// SIZE 0x34

extern int g_772610;
extern int g_77260c;

void __cdecl fcn_00475f80(Item* p);
void __cdecl fcn_0041ddd0(void* p);

// FUNCTION: GOLDTL 0x47ac60
void __cdecl fcn_0047ac60(Group* g)
{
	int i;

	for (i = 0; i < g->count; i++) {
		g->items[i]->refs--;
		if (g->items[i]->refs <= 0) {
			g_772610 -= g->items[i]->size;
			fcn_00475f80(g->items[i]);
			g_77260c--;
		}
	}
	fcn_0041ddd0(g->extra);
	g->extra = 0;
	fcn_0041ddd0(g->items);
	g->items = 0;
	fcn_0041ddd0(g);
}
