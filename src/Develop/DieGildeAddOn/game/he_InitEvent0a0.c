extern int gm_AllEntitiesControllable;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x00562750 */
void __cdecl he_InitEvent0a0(char* o)
{
	if (o[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	if (gm_AllEntitiesControllable != 0) {
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 1, 0, 0);
	} else {
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
		*(short*) (o + 0x56) = gm_RandomMod(2) + 0x13;
	}
	*(int*) (o + 0x58) = 0;
	*(int*) (o + 0x84) = cm_SendSetHE(0, o);
}
