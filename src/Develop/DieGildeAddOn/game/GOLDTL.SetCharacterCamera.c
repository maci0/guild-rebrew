#include "Develop/DieGildeAddOn/game/ch_script.h"
#include <string.h>

extern char* evt_CurrentScript;

void __cdecl evt_LogScriptError(char*, int, const char*);
void __cdecl ch_SetCameraView(char*, int);


/* SetCharacterCamera(): puts the camera into one of the character views. */
/* ADDRESS: GOLDTL 0x0040d8c0 */
int __cdecl SetCharacterCamera(char** ch, char** view)
{
	if (*ch == 0) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "SetCharacterCamera(): Invalid character");
		return 1;
	}
	if (strcmp("CLOSEUP", *view) == 0) {
		ch_SetCameraView(*ch, 0);
	} else if (strcmp("LEFT_SHOULDER", *view) == 0) {
		ch_SetCameraView(*ch, 1);
	} else if (strcmp("RIGHT_SHOULDER", *view) == 0) {
		ch_SetCameraView(*ch, 2);
	} else if (strcmp("EGO", *view) == 0) {
		ch_SetCameraView(*ch, 3);
	}
	return 0;
}
