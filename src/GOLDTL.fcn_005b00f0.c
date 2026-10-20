#include <math.h>

extern char g_1043370[];
extern int g_778d20;
extern int g_778d24;

/* ADDRESS: GOLDTL 0x005b00f0 */
void __cdecl fcn_005b00f0(char* obj, int a2, int a3)
{
	float t;
	float a;
	float b;
	float v;
	float w;

	t = (float) *(int*) (*(char**) g_1043370 + 0x20) * 0.5;
	a = (float) ((float) *(int*) (obj + 8) - t) * 5.33f;
	b = (float) ((float) *(int*) (obj + 0xc) - t) * 5.33f;
	v = (float) fabs(a) / ((float) g_778d24 * 0.5f) * 51.0f;
	if (a < 0.0f) {
		v = a - v;
	} else {
		v = v + a;
	}
	w = (float) fabs(b) / ((float) g_778d20 * 0.5f) * 51.0f;
	if (b < 0.0f) {
		w = b - w;
	} else {
		w = w + b;
	}
	*(float*) (obj + 0x10) = (float) a2 + (float) g_778d24 * 0.5f + v;
	*(float*) (obj + 0x14) = (float) g_778d20 * 0.5f + (float) a3 + w;
}
