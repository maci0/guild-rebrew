



extern unsigned int g_6b6f38;
extern unsigned int* g_6b6d18;
extern unsigned char d3_OctreePalette[3][0x100];

/* ADDRESS: GOLDDE 0x0041a6b0 */
int __cdecl d3_FindNearestPaletteColor(int r, int g, int b)
{
	unsigned int i;
	unsigned int d;
	unsigned int best;
	int bi;

	r = (r & 0xf8) + 4;
	g = (g & 0xf8) + 4;
	b = (b & 0xf8) + 4;
	best = 200000;
	for (i = 0; i < g_6b6f38; i++) {
		d = g_6b6d18[d3_OctreePalette[0][i] - r] + g_6b6d18[d3_OctreePalette[2][i] - b];
		d += g_6b6d18[d3_OctreePalette[1][i] - g];
		if (d < best) {
			best = d;
			bi = i;
		}
	}
	return bi;
}
