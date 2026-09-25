typedef struct Pair0c {
	int key;
	int val;
	int pad;
} Pair0c;
// SIZE 0xc

extern Pair0c g_1011980[6];

// FUNCTION: GOLDTL 0x473690
// SIZE: 98
void __cdecl fcn_00473690(int key, int amt)
{
	int i;
	int a;

	if (amt == 0) {
		return;
	}
	for (i = 0, a = 0x1011980; a < 0x10119c8; a += 0xc, i++) {
		if (*(int*) a == key) {
			break;
		}
	}
	if (i == 6) {
		for (i = 0, a = 0x1011980; a < 0x10119c8; a += 0xc, i++) {
			if (*(int*) a == -1) {
				break;
			}
		}
		if (i == 6) {
			return;
		}
	}
	g_1011980[i].key = key;
	g_1011980[i].val += amt;
}
