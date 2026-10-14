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
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x0047ac60 */
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
	m_FreeTracked(g->extra);
	g->extra = 0;
	m_FreeTracked(g->items);
	g->items = 0;
	m_FreeTracked(g);
}
