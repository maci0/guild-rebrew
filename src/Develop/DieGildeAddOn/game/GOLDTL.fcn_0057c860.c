#include "Develop/client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x0057c860 */
/* ADDRESS: GOLDDE 0x00562690 */
void __cdecl he_ScheduleZigeunerActionExpiry(char* o)
{
	*(int*) (o + 0x70) = -1;
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
}
