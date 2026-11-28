


#include "Develop/DieGildeAddOn/game/game_data.h"
void __cdecl msx_RegisterAILShutdown(void);
__declspec(dllimport) int __stdcall AIL_startup(void);
__declspec(dllimport) char* __stdcall AIL_last_error(void);

/* ADDRESS: GOLDDE 0x00424a10 */
int __cdecl msx_InitAIL(void)
{
	int r = 0;

	if (msx_Initialized == 0) {
		msx_RegisterAILShutdown();
		AIL_startup();
		AIL_last_error();
		msx_Initialized = -1;
	} else {
		r = -1;
	}
	return r;
}
