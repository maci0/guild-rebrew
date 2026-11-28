typedef struct {
	char pad0[0x48];
	int refs;
} D2_SHAPE_SURFACE;

typedef struct {
	char pad0[0x24];
	int count;
	D2_SHAPE_SURFACE** items;
} D2_SHAPE_NODE;

typedef struct {
	char pad0[0x4];
	unsigned short count;
	char pad6[0x12];
	D2_SHAPE_NODE** nodes;
} D2_SHAPE_BANK;
// SIZE 0x1c


/* ADDRESS: GOLDTL 0x0047ac20 */
/* ADDRESS: GOLDDE 0x00469c10 */
void __cdecl d2_AppendShapeNode(D2_SHAPE_NODE* n, D2_SHAPE_BANK* l)
{
	int i;

	l->nodes[l->count] = n;
	for (i = 0; i < n->count; i++)
		n->items[i]->refs++;
	l->count++;
}
