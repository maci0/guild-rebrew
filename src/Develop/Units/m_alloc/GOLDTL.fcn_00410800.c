


extern char* g_6b7e98;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_004526d0(char* e, float* v);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_00410800(char** a, int* x, int* y, int* z)
{
	float v[4];
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	v[0] = (float) *x;
	v[1] = (float) *y;
	v[2] = (float) *z;
	fcn_004526d0(e, v);
	return 0;
}
