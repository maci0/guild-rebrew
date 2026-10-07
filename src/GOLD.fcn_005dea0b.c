// FUNCTION: GOLD 0x005dea0b
// fcn_005dea0b — call [0x62de78] if set; 2 fcn_005deaf3 pairs.

void __cdecl fcn_005deaf3(void*, void*);

void __cdecl fcn_005dea0b(void)
{
	if (*(int*) 0x62de78 != 0) {
		((void (__stdcall*)()) *(void**) 0x62de78)();
	}
	fcn_005deaf3((void*) 0x5f1008, (void*) 0x5f1018);
	fcn_005deaf3((void*) 0x5f1000, (void*) 0x5f1004);
}

// FUNCTION: GOLDTL 0x64e63d
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

/* initterm helper: calls the single function pointer at 0x100317d8 (if
 * set), then walks the two .rdata init-vector tables via __initterm. */

extern void __cdecl __initterm(void*, void*);   /* 0x1001a758 - initterm loop */

void __cdecl fcn_1001a643(void)
{
    if (*(void**) 0x6b1f08 != 0)
        ((void (__cdecl*)(void)) *(void**) 0x6b1f08)();
    __initterm((void*)0x675008, (void*)0x67501c);
    __initterm((void*)0x675000, (void*)0x675004);
}
