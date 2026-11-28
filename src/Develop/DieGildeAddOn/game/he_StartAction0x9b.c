#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDTL 0x00577730 */
/* ADDRESS: GOLDDE 0x0055d650 */
void __cdecl he_StartAction0x9b(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0x30, 0, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}
