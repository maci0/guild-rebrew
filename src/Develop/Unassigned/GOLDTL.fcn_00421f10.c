typedef struct {
	char pad16[0x16];
	unsigned short prev;
	unsigned short pad18;
	unsigned short next;
} PATH_LINK_NODE;
// SIZE 0x1c

typedef struct {
	char pad[0x24];
	PATH_LINK_NODE* table;
} PATH_LINK_GRID;
// SIZE 0x28

/* ADDRESS: GOLDTL 0x00421f10 */
void __cdecl ReversePathLinks(PATH_LINK_GRID* grid, unsigned short startIndex)
{
	unsigned short v;
	unsigned short n;
	int tail;

	if (grid->table[startIndex].next == 0xffff) {
		return;
	}
	grid->table[startIndex].prev = 0xffff;
	v = startIndex;
	tail = (int) startIndex;
	while (v != 0xffff) {
		n = grid->table[v].next;
		if (n != 0xffff) {
			tail = (int) n;
			grid->table[n].prev = v;
			n = grid->table[v].next;
		}
		v = n;
	}
	while (tail != 0xffff) {
		grid->table[tail].next = grid->table[tail].prev;
		tail = (int) grid->table[tail].prev;
	}
}
