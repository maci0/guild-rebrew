

extern int g_1043030[];
extern int g_1043040[];
extern int g_1042a2c;
extern int g_1043298;

/* ADDRESS: GOLDDE 0x0044b450 */
void __cdecl d3_SetupRightEdgeStep(int topIdx, int botIdx)
{
	int y0;
	int dy;
	int x0;
	int slope;

	y0 = g_1043040[topIdx];
	dy = g_1043040[botIdx] - y0;
	x0 = g_1043030[topIdx];
	if (dy < 0x10000) {
		slope = (g_1043030[botIdx] - x0 * (0x40000000 / dy)) >> 14;
	} else {
		slope = (int) (((__int64) g_1043030[botIdx] - x0) * 0x10000 / dy);
	}
	g_1042a2c = slope;
	g_1043298 = ((((y0 + 0xffff) & ~0xffff) - y0) * slope >> 16) + x0;
}
