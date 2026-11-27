extern char g_774964;
#include "Develop/DieGildeAddOn/game/game_data.h"




void __cdecl fcn_005800b0(void);
void __cdecl d2_ResetTutorialStep(void);
void __cdecl he_FreeAction(char*);
void __cdecl main_ExitToFrameHandler(void*);
void __cdecl main_RunGameLoop(void);
int __cdecl fcn_0057e0a0(void);
int __cdecl d2_OpenTutorialMainDialog(void);

void __cdecl he_UpdateTutorialEvent(char* o)
{
	if (g_774964 != 0) {
		switch (*(int*) (o + 0x70)) {
		case 2:
			fcn_005800b0();
			d2_ResetTutorialStep();
			he_FreeAction(o);
			g_774954 = 1;
			main_ExitToFrameHandler((void*) main_RunGameLoop);
			break;
		case 1:
			if (fcn_0057e0a0() != 0) {
				*(int*) (o + 0x70) = 2;
			}
			break;
		case 0:
			*(int*) (o + 0x70) = (d2_OpenTutorialMainDialog() != 0) + 1;
			break;
		}
	}
}
