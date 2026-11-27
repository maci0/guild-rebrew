

extern int g_7766a8;
extern int main_LoopFlags;
extern char g_774660;
extern float g_675308;
extern char g_14cf950;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern float g_665e40;
extern char g_6a33b4[];

int __cdecl d2_TutorialAllowsFlag(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_AppendText(int);
int __cdecl main_RunFrameLoop(void (__cdecl*)(void), int);
void __cdecl d2_DestroyForm(int);
/* ADDRESS: GOLD 0x530820 */

void __cdecl main_RunAdvanceGameDialog(void)
{
	int saved;
	int flags;
	int h;

	saved = g_7766a8;
	flags = main_LoopFlags;
	if (d2_TutorialAllowsFlag(8) != 0) {
		fcn_0057e880(0xb, 0, 0, 0);
		flags = (flags & 0xffffc3e7) | 0xc0;
		g_774660 = 1;
		g_7766a8 = 0x2ee;
		g_675308 = 4.9375f;
		h = d2_LoadForm(0, 0, g_6a33b4);
		d2_CenterDialogWindows(h);
		io_AppendText(0x82);
		while (main_RunFrameLoop(main_RunAdvanceGameDialog, flags) != 0) {
			if (g_14cf950 != 0 || g_14ce8cc != 0 || g_14ce8e0 != 0) {
				g_774654 = 1;
			}
		}
		g_7766a8 = saved;
		g_774660 = 0;
		g_675308 = (float) (saved * g_665e40 + 0.25);
		d2_DestroyForm(h);
		fcn_0057e880(0xb, 0, 1, 0);
	}
}
