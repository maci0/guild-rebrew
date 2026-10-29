typedef struct {
	char pad16[0x16];
	unsigned short prev;
	unsigned short pad18;
	unsigned short next;
} Node_00421f10;
// SIZE 0x1c

typedef struct {
	char pad[0x24];
	Node_00421f10* table;
} Obj_00421f10;
// SIZE 0x28

/* ADDRESS: GOLDTL 0x00421f10 */
void __cdecl fcn_00421f10(Obj_00421f10* a0, unsigned int a1)
{
	unsigned short v;
	unsigned short n;
	int tail;

	v = (unsigned short) a1;
	if (a0->table[v].next == 0xffff) {
		return;
	}
	a0->table[v].prev = 0xffff;
	tail = (int) a1;
	if (v != 0xffff) {
		for (n = a0->table[v].next; n != 0xffff; n = a0->table[v].next) {
			a0->table[n].prev = v;
			v = n;
			tail = (int) n;
		}
	}
	while (tail != 0xffff) {
		a0->table[tail].next = a0->table[tail].prev;
		tail = (int) a0->table[tail].prev;
	}
}
