#include "Develop/client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x00575470 */
void __cdecl he_StartMissionCheck(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	*(int*) (o + 0xac) = -1;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 0xa, 0);
}
