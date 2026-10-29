extern int g_67a370;
extern float g_6628a8;
extern float g_662a98;

float __cdecl fcn_004d3070(char* self, int x, int z, float range);

/* ADDRESS: GOLDTL 0x004d3330 */
int __cdecl fcn_004d3330(char* self, int a1, int a2, int a3,
	unsigned int* a4, unsigned int* a5)
{
	char* map;
	char* cells;
	float best;
	float f;
	int i;
	int r;
	int c;
	int n;
	int d;
	int lo;
	int hi;
	int w;

	map = *(char**) (((char*) g_67a370) + 0xb0);
	best = 0.0f;
	i = 0;
	if (a3 > 0) {
		do {
			w = *(int*) (map + 0x20);
			hi = w - 1;
			if (hi > i + a2) {
				hi = i + a2;
			}
			lo = a2 - i;
			if (lo < 0) {
				lo = 0;
			}
			n = a2 - lo;
			for (r = lo; r <= hi; r++, n--) {
				d = i - (n < 0 ? -n : n);
				lo = a1 - d;
				if (lo < 0) {
					lo = 0;
				}
				hi = a1 + d;
				if (hi > w - 1) {
					hi = w - 1;
				}
				cells = *(char**) (map + 0x24);
				for (c = lo; c <= hi; c++) {
					if (*(int*) (cells + (w * r + c) * 0x1c) != 0
						&& *(int*) (cells + (w * r + c) * 0x1c) != 0xd) {
						f = fcn_004d3070(self, c, r,
							(float) a3 * *(float*) (map + 0x10) * 2.0f);
						if (f > best) {
							best = f;
							*a4 = c;
							*a5 = r;
						}
					}
				}
			}
			i++;
		} while (i < a3);
	}
	if (best != g_6628a8 && best > g_662a98) {
		return 1;
	}
	return 0;
}
