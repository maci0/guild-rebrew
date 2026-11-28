

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDDE 0x0054fa80 */
void __cdecl he_StartLoesegeld(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 1, gm_RandomMod(0x1e) - 0x14, 0);
}
