typedef struct {
	char pad0[0x48];
	int refs;
} fcn_0047ac20_item;

typedef struct {
	char pad0[0x24];
	int count;
	fcn_0047ac20_item** items;
} fcn_0047ac20_node;

typedef struct {
	char pad0[0x4];
	unsigned short count;
	char pad6[0x12];
	fcn_0047ac20_node** nodes;
} fcn_0047ac20_list;
// SIZE 0x1c

/* ADDRESS: GOLDTL 0x0047ac20 */

void __cdecl fcn_0047ac20(fcn_0047ac20_node* n, fcn_0047ac20_list* l)
{
	int i;

	l->nodes[l->count] = n;
	for (i = 0; i < n->count; i++)
		n->items[i]->refs++;
	l->count++;
}
