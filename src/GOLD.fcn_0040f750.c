

// SIZE 0x2
typedef struct {
	unsigned char kind : 5;
	unsigned char f5 : 1;
	unsigned char f6 : 1;
	unsigned char f7 : 1;
	unsigned char g0 : 1;
} Bits;

extern char* g_6b7e98;
#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

int __cdecl fcn_0040f750(char** a, unsigned char* k)
{
	char* e;

	e = *a;
	if (!m_is_tracked(e)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
		return 0;
	}
	((Bits*) (e + 0xcc))->kind = *k;
	return 0;
}
