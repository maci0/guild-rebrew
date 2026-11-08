#include "Develop/DieGildeAddOn/game/ch_script.h"
extern char* g_6b7e98;
extern char g_6761c8[];



void __cdecl fcn_00425bf0(int*, int, char*);
#include "Develop/DieGildeAddOn/game/ch_queue.h"

int __cdecl StopCharacter(void* a1)
{
	void* p;

	p = *(void**) a1;
	if (p == 0) {
		fcn_00425bf0(((int*)g_6b7e98), *(int*) ((char*) ((int*)g_6b7e98) + 0x118), g_6761c8);
	} else {
		ch_CancelActionQueue(p);
	}
	return 0;
}
