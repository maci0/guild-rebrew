

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_004107b0(char** a1)
{
	char* p;

	p = *a1;
	if (m_is_tracked(p) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676cf8);
		return 0;
	}
	p[0xd5] |= 2;
	return 0;
}
