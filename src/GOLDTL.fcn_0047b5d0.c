typedef struct {
	char pad0[0x4];
	unsigned short count;
	char pad6[0x12];
	void** nodes;
} fcn_0047b5d0_list;
// SIZE 0x1c

void __cdecl fcn_0047ac60(void*, fcn_0047b5d0_list*);
void __cdecl fcn_0041ddd0(void*);

// FUNCTION: GOLDTL 0x47b5d0

void __cdecl fcn_0047b5d0(fcn_0047b5d0_list* l)
{
	int i;

	for (i = 0; i < l->count; i++)
		fcn_0047ac60(l->nodes[i], l);
	fcn_0041ddd0(l->nodes);
	l->nodes = 0;
	fcn_0041ddd0(l);
}
