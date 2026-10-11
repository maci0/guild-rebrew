#include "Develop/DieGildeAddOn/game/ch_motion.h"

extern char g_6761a4[];
extern char g_6761a4[];

void __cdecl fcn_00425bf0(void*, int, void*);

int __cdecl fcn_0040dad0(int** pp)
{
	void* g;

	if (*pp == 0) {
		g = *(void**) ((char*)&g_6b7e98);
		fcn_00425bf0(g, *(int*) ((char*) g + 0x118), (void*) g_6761a4);
		return 0;
	}
	return *((int*) *pp + 0x128 / 4) == 0;
}
