extern char g_100f8c0[];
extern int g_67d8dc;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_00472880(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);


/* ADDRESS: GOLDTL 0x00475240 */
void __cdecl fcn_00475240(int a)
{
	if (g_100f8c0[0] != 0 && g_67d8dc != 0) {
		fcn_00472880(a);
		fcn_0046bd20(d2_MouseX - 0x36, d2_MouseY + 0x34, 0xa0, 0x60, g_77250c, g_100f8c0, 0xa8);
	}
}
