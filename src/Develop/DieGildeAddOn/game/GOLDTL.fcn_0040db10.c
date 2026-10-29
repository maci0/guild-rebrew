#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char* g_6b7e98;
extern char g_6761c8[];



void __cdecl fcn_00425bf0(int*, int, char*);
void __cdecl fcn_00406120(void*);

int __cdecl fcn_0040db10(void* a1)
{
	void* p;

	p = *(void**) a1;
	if (p == 0) {
		fcn_00425bf0(((int*)g_6b7e98), *(int*) ((char*) ((int*)g_6b7e98) + 0x118), g_6761c8);
	} else {
		fcn_00406120(p);
	}
	return 0;
}
