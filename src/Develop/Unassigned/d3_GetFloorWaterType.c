/* SIZE 0x14 */
typedef struct Run {
	int a;
	int y;
	int x0;
	int x1;
	unsigned char v;
} Run;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00446910 */
int __cdecl d3_GetFloorWaterType(int* g, int x, int y)
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
#else
/* ADDRESS: GOLDTL 0x00441f10 */
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
#endif
