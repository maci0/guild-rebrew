

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(void*, int, char*);

int __cdecl evt_SetEmitterSize(char** a1, int* a2, int* a3, int* a4)
{
	char* allocation;

	allocation = *a1;
	if (m_is_tracked(allocation) == 0) {
		evt_LogScriptError(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676ac0);
		return 0;
	}
	*(float*) (allocation + 0x68) = (float) *a2;
	*(float*) (allocation + 0x6c) = (float) *a3;
	*(float*) (allocation + 0x70) = (float) *a4;
	return 0;
}
