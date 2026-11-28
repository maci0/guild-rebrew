#include "Develop/client_types.h"
extern char d2_InventoryPanelWindowId[];

// fcn_005ba750 — fcn_00476c60(); fcn_00472cd0([0x6abb00]); [0x6abb00]=-1.


int __cdecl d2_CloseWindow(int);

void __cdecl d2_CloseInventoryPanel(void)
{
	ResetDisplayCounters();
	d2_CloseWindow(*(int*) &d2_InventoryPanelWindowId);
	*(int*) &d2_InventoryPanelWindowId = 0xffffffff;
}
