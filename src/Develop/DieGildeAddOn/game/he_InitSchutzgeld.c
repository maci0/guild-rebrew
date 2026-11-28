int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDDE 0x005397d0 */
void __cdecl he_InitSchutzgeld(char* o)
{
	*(int*) (o + 0x84) = -1;
	if ((o[0x78] & 4) == 0) {
		*(int*) (o + 0xb8) = -1;
		*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 2, 0);
		*(int*) (o + 0x70) = 1;
		*(int*) (o + 0x84) = cm_SendSetHE(1, o);
	}
}
