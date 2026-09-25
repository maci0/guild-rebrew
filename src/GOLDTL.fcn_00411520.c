#include <string.h>

typedef int (__stdcall* fcn_00411520_fn)(int, int, int, int, char*, int);

// GLOBAL: GOLD 0x5eb010
extern fcn_00411520_fn g_662008;

// FUNCTION: GOLD 0x004104b0
// SIZE: 39
// FUNCTION: GOLDTL 0x411520
// SIZE: 39

void __cdecl fcn_00411520(int a1, int a2, char* a3)
{
	g_662008(a1, a2, 0, 1, a3, strlen(a3) + 1);
}
