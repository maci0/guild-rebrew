#include <math.h>
#include <string.h>

extern int g_67dac0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern double dbl_1_0;

/* ADDRESS: GOLDTL 0x0047a570 */
int __cdecl fcn_0047a570(int a0, int a1, int a2, int* countOut, int* sizesOut, int a5)
{
	int tmp[8];
	int n;
	int size;
	int v1;
	int v2;
	int prod;
	int bp;

	unsigned int i;
	int k;

	if (a2 > a1) {
		n = a2;
	}
	else {
		n = a1;
	}
	if (a0 > 1) {
		v1 = (int) (sqrt((double) a0) + dbl_1_0);
	}
	else {
		v1 = a0;
	}
	n = v1 * n;
	i = n;
	size = 0;
	do {
		if (i <= 0) break; i >>= 1;
		size++;
	} while (size < 0x18);
	size--;
	if (size < 1) {
		size = 1;
	}
	size = 1 << size;
	if (size < n) {
		size += size;
	}
	if (g_67dac0 < size) {
		size = g_67dac0;
	}
	if ((float) n / (float) size < 0.9f && size > 0x40 && a5 != 0
	    && size / 2 > a2 && size / 2 > a1) {
		size >>= 1;
	}
	v1 = size / a1;
	v1 = (int) (1.0f > (float) v1 + 0.5f ? 1.0f : (float) v1 + 0.5f);
	v2 = size / a2;
	v2 = (int) (1.0f > (float) v2 + 0.5f ? 1.0f : (float) v2 + 0.5f);
	prod = v1 * v2;
	bp = a0 / prod < 1 ? 1 : a0 / prod;
	for (k = 0; k < bp; k++) {
		sizesOut[k] = size;
	}
	if (bp >= 1 && a0 % prod != 0 && a0 > prod && a5 != 0) {

		fcn_0047a570(a0 % prod, a1, a2, &a0, tmp, 0);
		if (a0 > 0) {
			memcpy(&sizesOut[bp], tmp, a0 * 4);
			bp += a0;
		}
	}
	*countOut = bp;
	return 1;
}
