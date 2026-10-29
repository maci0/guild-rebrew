#include "client_sound.h"

extern int g_772d14;
extern int g_772d10;
extern int g_772d28;
extern int g_774930;

void __cdecl fcn_004c24c0(float, int);


/* ADDRESS: GOLDTL 0x004c2d50 */
void __cdecl fcn_004c2d50(void)
{
	g_772d28 = 0;
	(*(char*)&g_772d10) = (*(char*)&g_772d14);
	if (g_774930 != 0 && g_772d1c != g_772d24)
		fcn_004c24c0(1.0f, 3000);
}
