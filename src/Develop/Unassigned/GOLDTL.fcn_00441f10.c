

// SIZE 0x14
typedef struct Run {
	int a;
	int y;
	int x0;
	int x1;
	unsigned char v;
} Run;

int __cdecl d3_GetFloorWaterType(int* floor, int x, int y)
{
	Run* p;

	if (x > 0 && y > 0 && x < floor[0] && y < floor[0]) {
		p = *(Run**) ((char*) floor + 0x258 + ((y / floor[1]) * 8 + x / floor[1]) * 0x1f4);
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
