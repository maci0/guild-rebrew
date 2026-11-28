typedef struct
{
	void* pad[2];
	int (__stdcall* Release)(void*);
} D3S_CACHE_VTBL;
// SIZE 0xc

extern unsigned long d3_LastReleaseRefCount;
extern unsigned int g_10405fc;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int* d3_InteriorSupermap;

void __cdecl d3s_FreeCache(void);
void __cdecl gv_Free3Fields(int* slot);

/* ADDRESS: GOLDTL 0x00456cf0 */
/* ADDRESS: GOLDDE 0x0044c4b0 */
void __cdecl d3s_ReleaseCache(void)
{
	int a;
	void* o;

	for (a = ((int) &g_10405fc + 0x14); a <= ((int) &g_10405fc + 0x1c); a += 4) {
		o = *(void**) a;
		if (o != 0) {
			(*(int*)&d3_LastReleaseRefCount) = (*(D3S_CACHE_VTBL**) o)->Release(o);
			*(void**) a = 0;
		}
	}
	(*(int*)&g_10405fc) = 0;
	(*(int*)&g_104061c) = 0;
	d3s_FreeCache();
	if (d3_InteriorSupermap != 0) {
		gv_Free3Fields(d3_InteriorSupermap);
		d3_InteriorSupermap = 0;
	}
}
