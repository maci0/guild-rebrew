typedef struct Card {
	int rank;
	int suit;
	int count;
	int owner;
} Card;
// SIZE 0x10

extern Card g_1007ce0[24];

// FUNCTION: GOLDTL 0x4a7770
// SIZE: 126
int __cdecl fcn_004a7770(int* h, int a2, int skip, int* out)
{
	int counts[6];
	int k;
	int g;
	int j;
	int c;
	int max;

	for (k = 1; k < 3; k++) {
		max = 0;
		for (g = 0; g < 6; g++) {
			c = 0;
			for (j = 0; j < 4; j++) {
				if (g_1007ce0[g * 4 + j].count == k && (!a2 || g_1007ce0[g * 4 + j].owner != 0)) {
					c++;
				}
			}
			if (c > max) {
				max = c;
			}
			counts[g] = c;
		}
	}
	for (g = 0; g < 6; g++) {
		if (g != skip && counts[g] > 1) {
			*out = g;
			return counts[g];
		}
	}
	return 0;
}
