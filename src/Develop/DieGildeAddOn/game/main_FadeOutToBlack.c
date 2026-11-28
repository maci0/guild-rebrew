#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_7e1d40;



#include "Develop/DieGildeAddOn/game/client_timer.h"
void __cdecl d2_LoadingScreenTimerCallback(void);
unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_ClearBackdropResource(void);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);

/* ADDRESS: GOLDDE 0x00526230 */
void __cdecl main_FadeOutToBlack(void)
{
	int flags;
	unsigned char* p;

	flags = 0x24087;
	if (nt_ClientSocket == -1) {
		flags = 0x24086;
	}
	tb_CloseFunction(d2_LoadingScreenTimerCallback);
	p = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x1e, 1);
	while ((*p & 4) == 0) {
		main_RunFrameLoop(0, flags);
	}
	d2_DestroyForm(g_7e1d40);
	d2_ClearBackdropResource();
	d2_ClearSurface(d2_ScreenSurface);
	d2_SuppressOverlay = 0;
	d2_ReleaseOverlaySprite(p);
}
