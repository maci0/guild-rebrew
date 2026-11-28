

#include <string.h>

extern char* d2_Controls;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_102d150[];
extern char g_102d29c[];
extern int main_LoopFlags;
extern char io_LastKeyScancode;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int tp_d2_SelectedControl;

int __cdecl d2_OpenInputIcon(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SelectControl(int);
void __cdecl d2_SetBildArgument(int, int);
int __cdecl main_RunFrameLoop(void*, int);
char* __cdecl d2_GetControlValue(int);
void __cdecl d2_DestroyElement(int);

/* ADDRESS: GOLDDE 0x005c20a0 */
int __cdecl d2_EditSlotTextInput(int a, int b, char* text)
{
	int result;
	int h;

	result = 0;
	h = d2_OpenInputIcon(a, b, 0, d2_FontHeight, 1);
	d2_SetElementFont(h, 0x53);
	d2_SetElementValue(h, text);
	d2_SelectControl(h);
	*(int*) (g_102d150 + *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h].value_088)) * 0x160) = 0x80;
	*(int*) (g_102d29c + *(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[h].value_088)) * 0x160) = 0x110;
	d2_SetBildArgument(h, 0x1f);
	while (main_RunFrameLoop(d2_EditSlotTextInput, main_LoopFlags) != 0) {
		if ((*(unsigned char*)&io_LastKeyScancode) == 0x1c) {
			strcpy(text, d2_GetControlValue(h));
			d2_DialogCloseRequested = 1;
			result = 1;
		}
		if (io_RightButtonReleased != 0 || tp_d2_SelectedControl == 0) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_DestroyElement(h);
	return result;
}
