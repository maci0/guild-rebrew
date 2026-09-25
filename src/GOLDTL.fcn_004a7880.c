typedef struct Card {
	int rank;
	int suit;
	int count;
	int owner;
} Card;
// SIZE 0x10

extern Card g_1007ce0[24];

extern char* g_1007cd4;

unsigned short __cdecl fcn_0042e410(int n);

// FUNCTION: GOLD 0x004a7760
// SIZE: 117
// FUNCTION: GOLDTL 0x4a7880
// SIZE: 117
int __cdecl fcn_004a7880(int owner)
{
	int i;

	if (!g_1007cd4[0xb4]) {
		return -1;
	}
	if ((unsigned char) g_1007cd4[0xb4] > 10) {
		do {
			i = fcn_0042e410(0x18);
		} while (g_1007ce0[i].count != 3);
	} else {
		for (i = 0; i < 24; i++) {
			if (g_1007ce0[i].count == 3) {
				break;
			}
		}
	}
	g_1007ce0[i].count = owner;
	g_1007cd4[0xb4]--;
	return i;
}
