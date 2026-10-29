extern char* g_6b7e98;
extern char g_676c24[];


// SIZE 0xcd
typedef struct {
	char pad[0xcc];
	unsigned char b0 : 6;
	unsigned char b6 : 1;
} S410600;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040f6f0(S410600** a1, char* a2)
{
	S410600* p;

	p = *a1;
	if (m_is_tracked(p) == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) ((char*) g_6b7e98 + 0x118), g_676c24);
		return 0;
	}
	p->b6 = *a2;
	return 0;
}
