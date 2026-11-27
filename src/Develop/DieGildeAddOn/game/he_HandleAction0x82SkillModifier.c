


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_HandleAction0x82SkillModifier(char* u)
{
	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		*(int*) (u + 0x84) = cm_SendSetHE(-1, u);
	} else {
		he_FreeAction(u);
	}
}
