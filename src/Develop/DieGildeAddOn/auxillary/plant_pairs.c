/* plt_TableLookup and its table form their own translation unit between plant.c and
 * sim.c: the reference's .data has plant.c's string literals before the pair table, and
 * the pair table opens an 8-aligned TU .data block. */

/* 0x58 pairs read by plt_TableLookup; a struct
 * array, 8-aligned like the reference (four zero bytes at 0x1002da2c). */
// SIZE 0x8
typedef struct {
	int first;
	int second;
} PLANT_PAIR;

PLANT_PAIR g_plant_pair_table[0x58] = {
	{ 0, 0 },
	{ 0x320008, 0 },
	{ 0x4b000c, 0 },
	{ 0x7d0014, 0 },
	{ 0x80000, 0 },
	{ 0xc0000, 0 },
	{ 0xf0000, 0 },
	{ 0x140000, 0 },
	{ 0xa0000, 0x30000 },
	{ 0xf0000, 0x90000 },
	{ 0x190000, 0x100000 },
	{ 0x140000, 0x140006 },
	{ 0x1e0000, 0x3c0009 },
	{ 0x2d0000, 0x6e000c },
	{ 0x1e0000, 0xa0000 },
	{ 0x2d0000, 0x1e0000 },
	{ 0x460000, 0x3c0000 },
	{ 0xa0000, 0xa0000 },
	{ 0x140000, 0x1e0000 },
	{ 0x190000, 0x3c0000 },
	{ 0x1e0000, 0xf0003 },
	{ 0x2d0000, 0x320006 },
	{ 0x500000, 0x780009 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0xf0000 },
	{ 0x320000, 0x230000 },
	{ 0x4b0000, 0x460000 },
	{ 0, 0 },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x1e000a },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x640000, 0x140000 },
	{ 0x1e0000, 0x1e000c },
	{ 0xa0000, 0 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x140008 },
	{ 0x320000, 0x28000a },
	{ 0x4b0000, 0x50000c },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x140003 },
	{ 0x320000, 0x320005 },
	{ 0x4b0000, 0x640006 },
	{ 0x1e0000, 0x190004 },
	{ 0x320000, 0x280005 },
	{ 0x500000, 0x460006 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0x140000, 0x50000 },
	{ 0x280000, 0xa0000 },
	{ 0x500000, 0x140000 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
};
int g_plant_flag = 1;

/* Simple lookup into a global table by index. Returns value
 * through out-pointer. Returns 0 if index out of range. */

int __cdecl plt_TableLookup(int index, int* out)
{
	if (index >= 0x58) {
		return 0;
	}
	*out = *(int*) ((int) g_plant_pair_table + index * 8);
	*(int*) ((char*) out + 4) = *(int*) ((int) g_plant_pair_table + 4 + index * 8);
	return 1;
}
unsigned char _dpad_1002da30[704];
