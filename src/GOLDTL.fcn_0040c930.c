


extern char* g_6b7e98;
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

char* __cdecl fcn_0040c930(char** a, float* b, float* c, float* d)
{
	float v[4];
	char* o;

	v[0] = *b;
	v[1] = *c;
	v[2] = *d;
	o = fcn_00403b90(*a, v);
	if (o == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "object not created");
	} else {
		*(int*) (o + 0x30) = *(int*) (g_6b7e98 + 0x104);
	}
	return o;
}
