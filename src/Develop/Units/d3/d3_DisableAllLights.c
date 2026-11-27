typedef int(__stdcall* Fn3)(void* self, int a, int b);

#include "Develop/Units/d8_vesa/d3d_device_view.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern void* g_6b870c;

/* ADDRESS: GOLDTL 0x00450c70 */
void __cdecl d3_DisableAllLights(void)
{
	int i;

	for (i = 0; i < d3_MaxActiveLights; i++) {
		((Fn3) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_98[8])(((void**)g_6b5de0), i, 0);
		*(int*) (((char*)g_6b870c) + i * 0xc + 4) = 0;
	}
}
