

extern int g_6a9b9c;
extern int g_6a9b94;
extern int d2_CurrentWindowId;
extern int g_14b5d48;
extern int g_14b5d4c;
extern int g_14b5d50;
extern int g_9baadc;
#include "Develop/Units/d2.v1/d2_gui.h"
extern char g_6a9b90[];
extern char g_6a9b98[];

void __cdecl d2_SetForm(int, int);
void __cdecl d2_CreateButtonRow(int, int, char*, int, ...);

void __cdecl fcn_00593110(void)
{
	d2_SetForm(g_6a9b9c, 4);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, g_6a9b90, 2, g_14b5d48, g_14b5d4c);
	d2_SetForm(g_6a9b9c, 8);
	d2_CreateButtonRow(d2_CurrentWindowId, 0, g_6a9b98, 1, g_14b5d50);
	if (g_9baadc == 0x7f) {
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[g_6a9b94].disabled)) = 1;
	}
}
