extern int g_67a370;

float __cdecl fcn_004d3070(char* self, int x, int z, float range);

/* ADDRESS: GOLDTL 0x004d31d0 */
int __cdecl fcn_004d31d0(char* self, int a1, int a2, int a3,
	unsigned int* a4, unsigned int* a5)
{
	char* map;
	float best;
	float f;
	int i;
	int k;
	int r;
	int c;
	int n;
	int d;
	int lo;
	int hi;

	map = *(char**) (((char*) g_67a370) + 0xb0);
	best = 1e9f;
	i = 0;
	if (a3 > 0) {
		k = a2;
		do {
			hi = *(int*) (map + 0x20) - 1;
			if (hi > i + a2) {
				hi = i + a2;
			}
			lo = k < 0 ? 0 : k;
			n = a2 - lo;
			for (r = lo; r <= hi; r++, n--) {
				d = i - (n < 0 ? -n : n);
				lo = a1 - d;
				lo = lo < 0 ? 0 : lo;
				hi = a1 + d;
				if (hi > *(int*) (map + 0x20) - 1) {
					hi = *(int*) (map + 0x20) - 1;
				}
				for (c = lo; c <= hi; c++) {
					if (*(int*) (*(char**) (map + 0x24)
							+ (*(int*) (map + 0x20) * r + c) * 0x1c) != 0
						&& *(int*) (*(char**) (map + 0x24)
							+ (*(int*) (map + 0x20) * r + c) * 0x1c) != 0xd) {
						f = fcn_004d3070(self, c, r,
							(float) a3 * *(float*) (map + 0x10) * 2.0f);
						if (f < best) {
							best = f;
							*a4 = c;
							*a5 = r;
						}
					}
				}
			}
			i++;
			k--;
		} while (i < a3);
	}
	if (best != 1e9f) {
		return 1;
	}
	return 0;
}
