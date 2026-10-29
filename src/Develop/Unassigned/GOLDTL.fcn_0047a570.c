#include <math.h>
#include <string.h>

extern int g_67dac0;
extern float g_6628cc;
extern float g_6628a0;
extern double dbl_1_0;

/* ADDRESS: GOLDTL 0x0047a570 */
int __cdecl fcn_0047a570(int a0, int a1, int a2, int* a3, int* a4, int a5)
{
	int tmp[8];
	int n;
	int size;
	int v1;
	int v2;
	int prod;
	int bp;
	int cnt;
	int i;

	if (a1 > a2) {
		n = a1;
	}
	else {
		n = a2;
	}
	if (a0 > 1) {
		v1 = (int) (sqrt((double) a0) + dbl_1_0);
	}
	else {
		v1 = a0;
	}
	n = v1 * n;
	size = 0;
	i = n;
	while (i > 0 && size < 0x18) {
		i >>= 1;
		size++;
	}
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
	if ((double) n / (double) size < 0.9f && size > 0x40 && a5 != 0
	    && size / 2 > a1 && size / 2 > a2) {
		size >>= 1;
	}
	v1 = size / a1;
	v1 = (int) ((float) v1 + 0.5f < 1.0f ? (float) v1 + 0.5f : 1.0f);
	v2 = size / a2;
	v2 = (int) ((float) v2 + 0.5f < 1.0f ? (float) v2 + 0.5f : 1.0f);
	prod = v1 * v2;
	bp = a0 / prod;
	if (bp < 1) {
		bp = 1;
	}
	if (bp > 0) {
		for (i = 0; i < bp; i++) {
			a4[i] = size;
		}
	}
	if (bp >= 1 && a0 % prod != 0 && a0 > prod && a5 != 0) {
		cnt = 0;
		fcn_0047a570(a0 % prod, a1, a2, &cnt, tmp, 0);
		if (cnt > 0) {
			memcpy(&a4[bp], tmp, cnt * 4);
			bp += cnt;
		}
	}
	*a3 = bp;
	return 1;
}
