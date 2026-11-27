extern int g_1043030[];
extern int g_1043040[];
extern int g_10425f0[];
extern int g_1042a0c;
extern int g_1042a1c;
extern int g_1042a20;
extern int g_1043290;

/* ADDRESS: GOLDTL 0x00456400 */
void __cdecl d3_SetupLeftEdgeStep(int topIdx, int botIdx)
{
	int y0;
	int x0;
	int z0;
	int dy;
	int slope;
	int sx;
	int sz;
	int span;

	x0 = g_1043030[topIdx];
	y0 = g_1043040[topIdx];

	dy = g_1043040[botIdx] - y0;
	if (dy < 0x10000) {
		slope = 0x40000000 / dy; z0 = g_10425f0[topIdx];
		sx = (g_1043030[botIdx] - x0 * slope) >> 14;
		g_1042a1c = sx; sz = (g_10425f0[botIdx] - z0 * slope) >> 14;
	}
	else {
		sx = (int) (((__int64) g_1043030[botIdx] - x0) * 0x10000 / dy);
		z0 = g_10425f0[topIdx]; g_1042a1c = sx; sz = (int) (((__int64) g_10425f0[botIdx] - z0) * 0x10000 / dy);
	}

	g_1042a0c = sz;
	span = ((y0 + 0xffff) & 0xffff0000) - y0;
	g_1043290 = (sx * span >> 16) + x0;
	g_1042a20 = (sz * span >> 16) + z0;
}
