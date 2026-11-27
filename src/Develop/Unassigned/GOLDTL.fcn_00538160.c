extern char g_774944;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d2_ShutdownOverlayState(void);
void __cdecl fcn_005e12d0(void);
void __cdecl fcn_00465c60(void);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_00418bb0(void);
void __cdecl d3_Shutdown(void);
void __cdecl d3_ReleaseGraphicsInterfaces(void);
void __cdecl io_ShutdownInput(void);

void __cdecl fcn_00538160(void)
{
	g_774944 = 0;
	d2_SuppressOverlay = 1;
	d2_ShutdownOverlayState();
	fcn_005e12d0();
	fcn_00465c60();
	d3_SelectSceneContext(0, 1);
	fcn_00418bb0();
	d3_Shutdown();
	d3_ReleaseGraphicsInterfaces();
	io_ShutdownInput();
}
