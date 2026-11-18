typedef int(__stdcall* Fn3)(void* self, int a, int b);

extern void* g_6b5de0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern void* g_6b870c;

/* ADDRESS: GOLDTL 0x00450c70 */
void __cdecl fcn_00450c70(void)
{
	int i;

	for (i = 0; i < d3_MaxActiveLights; i++) {
		((Fn3) ((void**) *((void**)g_6b5de0))[0xb8 / 4])(((void**)g_6b5de0), i, 0);
		*(int*) (((char*)g_6b870c) + i * 0xc + 4) = 0;
	}
}
