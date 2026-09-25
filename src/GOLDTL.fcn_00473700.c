struct fcn_00473700_slot {
	int key;
	int count;
	int extra;
};
// SIZE 0xc

extern struct fcn_00473700_slot g_1011980[6];
// FUNCTION: GOLDTL 0x473700
// SIZE: 78

void __cdecl fcn_00473700(int key, int n)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (g_1011980[i].key == key)
			break;
	}
	if (i != 6) {
		g_1011980[i].count -= n;
		if (g_1011980[i].count == 0) {
			g_1011980[i].count = 0;
			g_1011980[i].key = -1;
		}
	}
}
