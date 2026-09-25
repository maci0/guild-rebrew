// FUNCTION: GOLDTL 0x455c90
// SIZE: 157

extern int g_1043030[];
extern int g_1043040[];
extern int g_1042a2c;
extern int g_1043298;

void __cdecl fcn_00455c90(int i, int j)
{
	int y0;
	int dy;
	int x0;
	int slope;

	y0 = g_1043040[i];
	dy = g_1043040[j] - y0;
	x0 = g_1043030[i];
	if (dy < 0x10000) {
		slope = (g_1043030[j] - x0 * (0x40000000 / dy)) >> 14;
	} else {
		slope = (int) (((__int64) g_1043030[j] - x0) * 0x10000 / dy);
	}
	g_1042a2c = slope;
	g_1043298 = ((((y0 + 0xffff) & ~0xffff) - y0) * slope >> 16) + x0;
}
