extern char g_774944;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d2_ShutdownOverlayState(void);
void __cdecl io_SaveIniSettings(void);
void __cdecl vfs_ShutdownResources(void);
void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_FreeRenderVertexBuffers(void);
void __cdecl d3_Shutdown(void);
void __cdecl d3_ReleaseGraphicsInterfaces(void);
void __cdecl io_ShutdownInput(void);

/* ADDRESS: GOLDDE 0x0051fa30 */
void __cdecl main_ShutdownSubsystems(void)
{
	g_774944 = 0;
	d2_SuppressOverlay = 1;
	d2_ShutdownOverlayState();
	io_SaveIniSettings();
	vfs_ShutdownResources();
	d3_SelectSceneContext(0, 1);
	d3_FreeRenderVertexBuffers();
	d3_Shutdown();
	d3_ReleaseGraphicsInterfaces();
	io_ShutdownInput();
}
