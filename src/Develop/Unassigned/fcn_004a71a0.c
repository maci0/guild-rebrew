#include "client_types.h"

extern Card_1007ce0 g_1007ce0[24];

int __cdecl fcn_004a7120(int* a, int* b, int c);
int __cdecl fcn_004a7770(int* a, int b, int c, int* out);

/* Collects the distinct cards named by a[0..3] into b[2..3] when their ranks
 * match the card selected by b[0]; b[0..1] keep their caller values. */
/* ADDRESS: GOLDTL 0x004a71a0 */
int __cdecl fcn_004a71a0(int* a, int* b, int c)
{
	int card;
	int out;
	int i;
	int j;

	if (c != 0) {
		return 0;
	}
	if (a[0] < 0 || a[1] < 0 || a[2] < 0 || a[3] < 0) {
		return 0;
	}
	if (fcn_004a7120(a, b, 0) == 0) {
		return 0;
	}
	card = g_1007ce0[b[0]].rank;
	if (fcn_004a7770(a, 0, card, &out) != 2) {
		return 0;
	}
	j = 2;
	for (i = 0; i < 5; i++) {
		if (g_1007ce0[a[i]].rank == out) {
			b[j] = a[i];
			j++;
			if (j == 4) {
				return 1;
			}
		}
	}
	return 0;
}
