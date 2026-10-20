#include <math.h>
#include <stdlib.h>

extern unsigned char g_773d75;
extern float g_6652d8[];

int __cdecl gm_WalkEntityChain(unsigned short raw_idx);
int __cdecl fcn_0050b710(int a, unsigned char k);
int __cdecl fcn_0050b750(int a, unsigned char k);

/* ADDRESS: GOLDTL 0x004f4440 */
int __cdecl fcn_004f4440(int handle, int value, int mode, int flag, int* out)
{
	double v;
	double f;
	double bright;
	int r;

	v = (double) fcn_0050b710(gm_WalkEntityChain(*(unsigned short*) handle), g_773d75);
	v = __min(1000000.0, v);
	v = __max(v, 10000.0);
	v = __min(1000000.0, v);
	f = log10(v);
	v = 100.0 * f * f;
	if (mode == 0) {
		v *= 0.25;
	} else if (mode == 1) {
		v *= 0.5;
	} else if (mode == 2) {
		v *= 0.75;
	}
	if (flag == 0) {
		bright = (double) (value & 0xff) / 255.0;
		bright = bright * 0.7f + 0.3f;
		v = bright * (v * 0.75f);
	}
	r = fcn_0050b750((int) v, g_773d75);
	*out = (int) (r * g_6652d8[mode]);
	return r;
}
