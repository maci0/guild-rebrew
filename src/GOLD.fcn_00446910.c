// FUNCTION: GOLD 0x446910
// SIZE: 114

// SIZE 0x14
typedef struct Run {
	int a;
	int y;
	int x0;
	int x1;
	unsigned char v;
} Run;

int __cdecl fcn_00446910(int* g, int x, int y)
{
	Run* p;

	if (x > 0 && y > 0 && x < g[0] && y < g[0]) {
		p = *(Run**) ((char*) g + 0x114 + ((y / g[1]) * 8 + x / g[1]) * 0x64);
		if (p != 0) {
			for (; p != 0 && p->y >= 0; p++) {
				if (y == p->y && x >= p->x0 && x <= p->x1) {
					return p->v;
				}
			}
		}
	}
	return -1;
}
