#include <math.h>

extern char g_1043370[];
extern int g_778d20;
extern int g_778d24;

/* ADDRESS: GOLDTL 0x005b00f0 */
void __cdecl fcn_005b00f0(char* obj, int a2, int a3)
{
	double t;
	float a;
	float b;
	double v;
	float w;

	t = (double) *(int*) (*(char**) g_1043370 + 0x20) * 0.5;
	a = (float) ((*(int*) (obj + 8) - t) * 5.33f);
	b = (float) ((*(int*) (obj + 0xc) - t) * 5.33f);
	v = fabs(a) / ((float) g_778d24 * 0.5f);
	w = (float) fabs(b) / ((float) g_778d20 * 0.5f);
	if (a < 0.0f) {
		v = a - v * 51.0f;
	} else {
		v = v * 51.0f + a;
	}
	if (b < 0.0f) {
		w = b - w * 51.0f;
	} else {
		w = w * 51.0f + b;
	}
	*(float*) (obj + 0x10) = (float) a2 + (float) g_778d24 * 0.5f + v;
	*(float*) (obj + 0x14) = (float) g_778d20 * 0.5f + (float) a3 + w;
}
