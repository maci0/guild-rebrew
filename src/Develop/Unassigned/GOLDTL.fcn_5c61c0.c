#include "client_types.h"
extern char g_6abb00[];

// fcn_005ba750 — fcn_00476c60(); fcn_00472cd0([0x6abb00]); [0x6abb00]=-1.


int __cdecl fcn_00472cd0(int);

void __cdecl fcn_005c61c0(void)
{
	ResetDisplayCounters();
	fcn_00472cd0(*(int*) &g_6abb00);
	*(int*) &g_6abb00 = 0xffffffff;
}
