extern char gm_InWorldHud;
#include "Develop/DieGildeAddOn/game/game_data.h"




void __cdecl d2_CleanupTutorialAction(void);
void __cdecl d2_ResetTutorialStep(void);
void __cdecl he_FreeAction(char*);
void __cdecl main_ExitToFrameHandler(void*);
void __cdecl main_RunGameLoop(void);
int __cdecl d2_StepTutorialStateMachine(void);
int __cdecl d2_OpenTutorialMainDialog(void);

/* ADDRESS: GOLDDE 0x005411f0 */
void __cdecl he_UpdateTutorialEvent(char* o)
{
	if (gm_InWorldHud != 0) {
		switch (*(int*) (o + 0x70)) {
		case 2:
			d2_CleanupTutorialAction();
			d2_ResetTutorialStep();
			he_FreeAction(o);
			g_774954 = 1;
			main_ExitToFrameHandler((void*) main_RunGameLoop);
			break;
		case 1:
			if (d2_StepTutorialStateMachine() != 0) {
				*(int*) (o + 0x70) = 2;
			}
			break;
		case 0:
			*(int*) (o + 0x70) = (d2_OpenTutorialMainDialog() != 0) + 1;
			break;
		}
	}
}
