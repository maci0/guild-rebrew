

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/client_dialog_state.h"

void __cdecl d2_CreateScrollPerga(void);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_UpdateScrollPerga(void);
void __cdecl d2_DestroyScrollPerga(void);

void __cdecl d2_RunScrollPerga(void)
{
	d2_CreateScrollPerga();
	while (main_RunFrameLoop(d2_RunScrollPerga, 0x657c7) != 0) {
		d2_UpdateScrollPerga();
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
	}
	d2_DestroyScrollPerga();
}
