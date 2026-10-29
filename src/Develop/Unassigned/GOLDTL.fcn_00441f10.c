

// SIZE 0x14
typedef struct Run {
	int a;
	int y;
	int x0;
	int x1;
	unsigned char v;
} Run;

int __cdecl fcn_00441f10(int* g, int x, int y)
{
	Run* p;

	if (x > 0 && y > 0 && x < g[0] && y < g[0]) {
		p = *(Run**) ((char*) g + 0x258 + ((y / g[1]) * 8 + x / g[1]) * 0x1f4);
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
