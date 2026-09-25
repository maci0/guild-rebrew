// FUNCTION: GOLD 0x421410
// SIZE: 142
// FUNCTION: GOLDTL 0x0041ca10
// SIZE: 142

extern unsigned int g_6b6f38;
extern unsigned int* g_6b6d18;
extern unsigned char g_6b6008[3][0x100];

int __cdecl fcn_0041ca10(int r, int g, int b)
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
		d = g_6b6d18[g_6b6008[0][i] - r] + g_6b6d18[g_6b6008[2][i] - b];
		d += g_6b6d18[g_6b6008[1][i] - g];
		if (d < best) {
			best = d;
			bi = i;
		}
	}
	return bi;
}
