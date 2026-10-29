extern char* g_entity_type_table;
extern unsigned char g_slot_table[2];

/* ADDRESS: GOLDTL 0x00505d00 */
int __cdecl fcn_00505d00(unsigned char* building, int* out)
{
	unsigned char* type;
	unsigned char* e;
	int* first;
	int* second;
	int* other;
	int count;
	int i;

	type = (unsigned char*) g_entity_type_table + building[0] * 0x24d;
	out[0] = 0;
	for (i = 0; i < 0x18; i++) {
		out[1 + i] = 0xffff;
	}
	for (i = 0; i < 0xc; i++) {
		out[0x19 + i] = 0xffff;
	}
	out[0x25] = 0xffff;
	first = out + 1;
	second = out + 0xd;
	other = out + 0x19;
	count = 0;
	for (i = 0, e = g_slot_table + 0x165; e < g_slot_table + 0x165 + 0x300 * 0x21c; i++, e += 0x21c) {
		if (*(unsigned char**) (e + 7) != building) {
			continue;
		}
		if (type[0x22f] == e[0]) {
			*first++ = *(unsigned short*) (e - 0x165);
		}
		else if (type[0x230] == e[0]) {
			*second++ = *(unsigned short*) (e - 0x165);
		}
		else if (type[0x223] != 0 && type[0x224] != 0 && (type[0x223] == e[-1] || type[0x224] == e[-1])) {
			out[0x25] = i;
		}
		else {
			*other++ = *(unsigned short*) (e - 0x165);
		}
		count++;
	}
	out[0] = count;
	return count;
}
