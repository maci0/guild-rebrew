typedef struct Tag {
	int id;
	int val;
	int pad;
} Tag;
// SIZE 0xc

extern Tag g_1011980[6];

// FUNCTION: GOLDTL 0x473750
// SIZE: 104
void __cdecl fcn_00473750(int id, int val)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (g_1011980[i].id == id) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0; i < 6; i++) {
			if (g_1011980[i].id == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	g_1011980[i].id = id;
	g_1011980[i].val = val;
	if (!val) {
		g_1011980[i].val = 0;
		g_1011980[i].id = -1;
	}
}
