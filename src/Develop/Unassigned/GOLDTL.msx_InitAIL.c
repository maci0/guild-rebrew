


#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl msx_RegisterAILShutdown(void);
__declspec(dllimport) int __stdcall AIL_startup(void);
__declspec(dllimport) char* __stdcall AIL_last_error(void);

int __cdecl msx_InitAIL(void)
{
	int r = 0;

	if (g_6b7f90 == 0) {
		msx_RegisterAILShutdown();
		AIL_startup();
		AIL_last_error();
		g_6b7f90 = -1;
	} else {
		r = -1;
	}
	return r;
}
