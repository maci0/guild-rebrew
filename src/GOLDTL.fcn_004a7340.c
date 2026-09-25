typedef struct Card {
	int rank;
	int suit;
	int count;
	int owner;
} Card;
// SIZE 0x10

extern Card g_1007ce0[24];

// FUNCTION: GOLDTL 0x4a7340
// SIZE: 161
int __cdecl fcn_004a7340(int* h, int* out, int a3)
{
	int s;
	int i;
	int k;
	int n;
	int rank;
	int* p;

	s = a3 ? 2 : 0;
	if (h[s] >= 0 && h[s + 1] >= 0 && h[s + 2] >= 0 && s < 3) {
		p = &h[s];
		i = s + 1;
		do {
			rank = g_1007ce0[*p].rank;
			out[0] = *p;
			n = 1;
			for (k = i; k < 5; k++) {
				if (h[k] < 0) {
					return 0;
				}
				if (g_1007ce0[h[k]].rank == rank) {
					out[n++] = h[k];
					if (n == 3) {
						return 1;
					}
				}
			}
			p++;
			i++;
		} while (i < 4);
	}
	return 0;
}
