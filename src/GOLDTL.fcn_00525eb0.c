// GLOBAL: GOLDTL 0x525e90
extern char g_525e90[];
// GLOBAL: GOLDTL 0x7e2760
extern char g_7e2760[];
// GLOBAL: GOLDTL 0x9ba1c0
extern char g_9ba1c0[];
// FUNCTION: GOLDTL 0x525eb0

#include <string.h>

void __cdecl fcn_0042de90(char*, int);

void __cdecl fcn_00525eb0(void)
{
	fcn_0042de90(g_525e90, 0x47);
	memset(g_7e2760, 0, 0x300);
	memset(g_9ba1c0, 0, 0x100);
}
