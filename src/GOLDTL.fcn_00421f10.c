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
	Obj_00421f10* o;
	unsigned short v;
	unsigned short n;
	int tail;

	o = a0;
	v = (unsigned short) a1;
	if (o->table[v].next == 0xffff) {
		return;
	}
	o->table[v].prev = 0xffff;
	tail = (int) a1;
	if (v != 0xffff) {
		for (n = o->table[v].next; n != 0xffff; n = o->table[v].next) {
			o->table[n].prev = v;
			v = n;
			tail = (int) n;
		}
	}
	if (tail != 0xffff) {
		do {
			o->table[tail].next = o->table[tail].prev;
			tail = (int) o->table[tail].prev;
		} while (tail != 0xffff);
	}
}
