#include "Develop/Units/d3/d3_object.h"
extern char* evt_CurrentScript;
extern char g_6766f0[];



void __cdecl evt_LogScriptError(int*, int, char*);

int __cdecl ecmd_KillObject(void* objectRef)
{
	void* p;

	p = *(void**) objectRef;
	if (p != 0) {
		d3_DestroyObject((D3_OBJECT*) (p));
		return 1;
	}
	evt_LogScriptError(((int*)evt_CurrentScript), *(int*) ((char*) ((int*)evt_CurrentScript) + 0x118), g_6766f0);
	return 1;
}
