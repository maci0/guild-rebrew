

#include "Develop/Units/m_alloc/m_alloc_checks.h"
int __cdecl fcn_00452420(int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040ffd0(int* a1)
{
	if (m_is_tracked((void*) *a1) != 0) {
		fcn_00452420(*a1);
	} else {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676a28);
	}
	return 0;
}
