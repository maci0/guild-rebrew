

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_004273d0(void*, int, char*);

int __cdecl SetEmitterSize(char** objectRef, int* firstValue, int* secondValue, int* thirdValue)
{
	char* p;

	p = *objectRef;
	if (m_is_tracked(p) == 0) {
		fcn_004273d0(*(void**) 0x6332b8, *(int*) ((char*) *(void**) 0x6332b8 + 0x118), (char*) 0x5f2a40);
		return 0;
	}
	*(float*) (p + 0x60) = (float) *firstValue;
	*(float*) (p + 0x64) = (float) *secondValue;
	*(float*) (p + 0x68) = (float) *thirdValue;
	return 0;
}
