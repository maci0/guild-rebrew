#include "client_types.h"

// fcn_005ba750 — fcn_00476c60(); fcn_00472cd0([0x62c418]); [0x62c418]=-1.


int __cdecl fcn_00472cd0(int);

void __cdecl fcn_005ba750(void)
{
	ResetDisplayCounters();
	fcn_00472cd0(*(int*) 0x62c418);
	*(int*) 0x62c418 = 0xffffffff;
}
