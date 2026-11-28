

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_MarkDialogFormControls(int);
void __cdecl d2_ClearScreen(void);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
void __cdecl d2_UpdateHudVisibility(int);
void __cdecl d2_RestoreHudPanels(void);

/* ADDRESS: GOLDDE 0x005c5190 */
void __cdecl d2_RestoreHudAfterPause(void)
{
	unsigned char* p;

	p = d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x1e, 1);
	while (!(*p & 4)) {
		main_RunFrameLoop(0, 0x24087);
	}
	if (g_774954 != 0) {
		d2_ClearScreen();
		d2_ReleaseOverlaySprite(p);
		g_774670 = 6;
		return;
	}
	((Rect*)&g_1040480)->right = ((Rect*)&g_6a3764)->right;
	((Rect*)&g_1040480)->left = ((Rect*)&g_6a3764)->left;
	((Rect*)&g_1040480)->top = ((Rect*)&g_6a3764)->top;
	((Rect*)&g_1040480)->bottom = ((Rect*)&g_6a3764)->bottom;
	d2_ClearScreen();
	d2_UpdateHudVisibility(1);
	d2_RestoreHudPanels();
	d2_MarkDialogFormControls(0);
	d2_ReleaseOverlaySprite(p);
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, g_67d67c, 0x32, 0xa);
}
