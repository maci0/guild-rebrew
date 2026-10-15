#include "Develop/DieGildeAddOn/game/ch_motion.h"



extern float g_662d40[3];
extern char* g_6b7e98;
void __cdecl fcn_00455350(char* src, char* pos, float* out);
void __cdecl fcn_00455140(char* src, float* v, float* out);
float __cdecl fcn_00451380(float* a, float* b);
void __cdecl fcn_00438cb0(char* h, float* v);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040de40(char** a, char** b)
{
	float v[3];
	float c[3];
	float p[4];

	if (*a == 0 || *b == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 1;
	}
	fcn_00455350(*b, *b + 0x4c, p);
	ch_SetPosition(*a, p, 1);
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	fcn_00455140(*b, g_662d40, c);
	v[1] = fcn_00451380(g_662d40, c);
	fcn_00438cb0(*(int*) (*a + 0x34), v);
	return 0;
}
