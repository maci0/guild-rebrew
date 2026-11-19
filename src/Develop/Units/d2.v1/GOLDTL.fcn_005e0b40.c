

#include <string.h>

extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_102d150[];
extern char g_102d29c[];
extern int main_LoopFlags;
extern char g_14cf950;
#include "client_dialog_state.h"
extern int tp_d2_SelectedControl;

int __cdecl d2_OpenInputIcon(int, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00474cf0(int);
void __cdecl d2_SetBildArgument(int, int);
int __cdecl fcn_005373e0(void*, int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_0046b2b0(int);

int __cdecl fcn_005e0b40(int a, int b, char* text)
{
	int result;
	int h;

	result = 0;
	h = d2_OpenInputIcon(a, b, 0, d2_FontHeight, 1);
	d2_SetElementFont(h, 0x53);
	d2_SetElementValue(h, text);
	fcn_00474cf0(h);
	*(int*) (g_102d150 + *(int*) (g_1015ea0 + h * 0x2f4 + 0x88) * 0x160) = 0x80;
	*(int*) (g_102d29c + *(int*) (g_1015ea0 + h * 0x2f4 + 0x88) * 0x160) = 0x110;
	d2_SetBildArgument(h, 0x1f);
	while (fcn_005373e0(fcn_005e0b40, main_LoopFlags) != 0) {
		if ((*(unsigned char*)&g_14cf950) == 0x1c) {
			strcpy(text, fcn_00471f80(h));
			g_774654 = 1;
			result = 1;
		}
		if (g_14ce8e0 != 0 || tp_d2_SelectedControl == 0) {
			g_774654 = 1;
		}
	}
	fcn_0046b2b0(h);
	return result;
}
