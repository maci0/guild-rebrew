// FUNCTION: GOLDTL 0x4a7240

typedef struct Card {
	int v;
	int a;
	int b;
	int c;
} Card;
// SIZE 0x10

typedef struct Hand {
	int c[5];
} Hand;
// SIZE 0x14

#include "client_types.h"
extern Card_1007ce0 g_1007ce0[24];

int __cdecl fcn_004a7240(Hand* in, Hand* out, int a3)
{
	int swapped;
	int k;
	int j;
	int t;

	swapped = 1;
	if (a3 != 0 || in->c[0] < 0 || in->c[1] < 0 || in->c[2] < 0 || in->c[3] < 0 || in->c[4] < 0) {
		return 0;
	}
	*out = *in;
	for (k = 0; k < 4 && swapped; k++) {
		swapped = 0;
		for (j = k + 1; j < 5; j++) {
			if (((Card*)g_1007ce0)[out->c[j]].v < ((Card*)g_1007ce0)[out->c[k]].v) {
				t = out->c[k];
				out->c[k] = out->c[j];
				swapped = 1;
				out->c[j] = t;
			}
		}
	}
	if (((Card*)g_1007ce0)[out->c[0]].v != 0) {
		return 0;
	}
	for (k = 0; k < 4; k++) {
		if (((Card*)g_1007ce0)[out->c[k + 1]].v <= ((Card*)g_1007ce0)[out->c[k]].v) {
			return 0;
		}
	}
	return 1;
}
