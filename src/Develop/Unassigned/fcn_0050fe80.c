#include "client_dialog_helpers.h"

/* ADDRESS: GOLDTL 0x0050fe80 */
int __cdecl fcn_0050fe80(char *base)
{
	float best;
	int best_index;
	int i;
	int value;

	best = 1.0e10f;
	best_index = -1;
	for (i = 0; i < 768; i++) {
		if (*(unsigned short *) (g_7f4ca0 + i * 0x21c) != 0xffff) {
			value = (signed char) base[0x869480 + i * 0x300];
			if (value < best) {
				best = value;
				best_index = i;
			}
		}
	}
	return best_index;
}
