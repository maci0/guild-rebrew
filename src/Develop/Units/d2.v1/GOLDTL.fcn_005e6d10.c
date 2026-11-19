

extern int g_6ad580;
extern int g_6ad568;
extern int d2_CurrentWindowId;
#include "client_types.h"
extern s_1015f4c g_1015f4c[];
extern int g_776644;
extern int g_776648;
extern unsigned char g_773d75;

void __cdecl d2_SetForm(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_0050b710(int, char);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetSlotVisibility(int, int);

void __cdecl fcn_005e6d10(int show)
{
	if (show != 0) {
		if (g_6ad580 == -1) {
			d2_SetForm(g_6ad568, 5);
			g_6ad580 = fcn_004677e0(0, 0, ((int*)g_1015f4c)[d2_CurrentWindowId * 243] - 0xb4, 0, 100, 0x7b, 2,
			    d2_CurrentWindowId);
			d2_SetElementValue(g_6ad580, fcn_0050b710(g_776644, (*(char*)&g_773d75)), fcn_0050b710(g_776648, (*(char*)&g_773d75)),
			    fcn_0050b710(g_776644, (*(char*)&g_773d75)), 1);
		}
		else {
			d2_SetSlotVisibility(g_6ad580, show);
		}
	}
}
