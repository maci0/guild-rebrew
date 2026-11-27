typedef struct
{
	void* pad[2];
	int (__stdcall* Release)(void*);
} D3S_CACHE_VTBL;
// SIZE 0xc

extern unsigned long g_14ce728;
extern unsigned int g_10405fc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int* g_6b89e4;

void __cdecl fcn_00456560(void);
void __cdecl gv_Free3Fields(int* slot);

/* ADDRESS: GOLDTL 0x00456cf0 */
void __cdecl d3s_ReleaseCache(void)
{
	int a;
	void* o;

	for (a = 0x1040610; a <= 0x1040618; a += 4) {
		o = *(void**) a;
		if (o != 0) {
			(*(int*)&g_14ce728) = (*(D3S_CACHE_VTBL**) o)->Release(o);
			*(void**) a = 0;
		}
	}
	(*(int*)&g_10405fc) = 0;
	(*(int*)&g_104061c) = 0;
	fcn_00456560();
	if (g_6b89e4 != 0) {
		gv_Free3Fields(g_6b89e4);
		g_6b89e4 = 0;
	}
}
