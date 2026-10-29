#include "Develop/Units/d3/d3_object.h"
extern char* g_6b7e98;
extern char g_6766f0[];



void __cdecl fcn_00425bf0(int*, int, char*);

int __cdecl ecmd_KillObject(void* a1)
{
	void* p;

	p = *(void**) a1;
	if (p != 0) {
		d3_DestroyObject((D3_OBJECT*) (p));
		return 1;
	}
	fcn_00425bf0(((int*)g_6b7e98), *(int*) ((char*) ((int*)g_6b7e98) + 0x118), g_6766f0);
	return 1;
}
