extern int g_1043030[];
extern int g_1043040[];
extern int g_10425f0[];
extern int g_1042a0c;
extern int g_1042a1c;
extern int g_1042a20;
extern int g_1043290;

/* ADDRESS: GOLDTL 0x00456400 */
void __cdecl fcn_00456400(int i, int j)
{
	int y0;
	int x0;
	int z0;
	int dy;
	int slope;
	int sx;
	int sz;
	int span;

	y0 = g_1043040[i];
	x0 = g_1043030[i];
	z0 = g_10425f0[i];
	dy = g_1043040[j] - y0;
	if (dy < 0x10000) {
		slope = 0x40000000 / dy;
		sx = (g_1043030[j] - x0 * slope) >> 14;
		sz = (g_10425f0[j] - z0 * slope) >> 14;
	}
	else {
		sx = (int) (((__int64) g_1043030[j] - x0) * 0x10000 / dy);
		sz = (int) (((__int64) g_10425f0[j] - z0) * 0x10000 / dy);
	}
	g_1042a1c = sx;
	g_1042a0c = sz;
	span = ((y0 + 0xffff) & 0xffff0000) - y0;
	g_1043290 = (sx * span >> 16) + x0;
	g_1042a20 = (sz * span >> 16) + z0;
}
