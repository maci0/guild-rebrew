#include "Develop/client_types.h"
extern char g_6abb00[];

// fcn_005ba750 — fcn_00476c60(); fcn_00472cd0([0x6abb00]); [0x6abb00]=-1.


int __cdecl d2_CloseWindow(int);

void __cdecl d2_CloseInventoryPanel(void)
{
	ResetDisplayCounters();
	d2_CloseWindow(*(int*) &g_6abb00);
	*(int*) &g_6abb00 = 0xffffffff;
}
