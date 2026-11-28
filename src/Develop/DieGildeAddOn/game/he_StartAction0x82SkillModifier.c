





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x00540df0 */
void __cdecl he_StartAction0x82SkillModifier(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime(e + 0x52, *(int*) (e + 0xb8), 0, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
	}
}
