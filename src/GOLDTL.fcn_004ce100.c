// FUNCTION: GOLD 0x004cd580
// SIZE: 68
// FUNCTION: GOLDTL 0x4ce100
// SIZE: 68

#include <string.h>

extern int g_9baa00;
extern int g_9baa08;
extern char g_9baa20[];
extern char g_9baae0[];
extern int g_9badd0;
extern int g_9badd4;

void __cdecl fcn_004ce100(int a1, int a2)
{
	memset(g_9baa20, 0, 0x24);
	memset(g_9baae0, 0, 0x2b8);
	g_9baa00 = 1;
	g_9badd0 = a1;
	g_9badd4 = a2;
	g_9baa08 = 0;
}
