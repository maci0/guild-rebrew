extern void* g_14d0020[];
// GLOBAL: GOLDTL 0x67536c
extern char g_67536c[];
// FUNCTION: GOLD 0x00402a30
// FUNCTION: GOLDTL 0x403270

#include <string.h>

int __cdecl fcn_0041db70(int, char*);

void* __cdecl fcn_00403270(int a1)
{
	void* p;

	p = (void*) fcn_0041db70(0x244, g_67536c);
	memset(p, 0, 0x244);
	if (g_14d0020[a1] != 0) {
		return 0;
	}
	g_14d0020[a1] = p;
	*(int*) p = a1;
	return p;
}
