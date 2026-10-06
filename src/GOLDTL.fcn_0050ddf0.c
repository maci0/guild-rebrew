// FUNCTION: GOLD 0x50a970
// FUNCTION: GOLDTL 0x0050ddf0

extern float g_6628a8;

int __cdecl fcn_0050ddf0(int v, int mode)
{
	int r;

	r = 0;
	if (v > g_6628a8) {
		if (v < 32000) {
			v = 32000;
		} else if (v > 256000) {
			v = 256000;
		}
	}
	if (mode == 1) {
		r = (int) (v * 0.05f);
	} else if (mode == 2) {
		r = (int) (v * 0.1f);
	} else if (mode == 3) {
		r = (int) (v * 0.15f);
	}
	return (int) (r + 0.5);
}
