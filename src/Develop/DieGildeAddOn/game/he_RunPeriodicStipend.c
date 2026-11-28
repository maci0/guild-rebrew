#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern int gm_EntityIdField[];
extern unsigned char gm_ActiveTownIndex;

void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_FreeAction(void*);

/* ADDRESS: GOLDTL 0x00551250 */
/* ADDRESS: GOLDDE 0x00537640 */
void __cdecl he_RunPeriodicStipend(char* u)
{
	switch (*(int*) (u + 0x70)) {
	case 0:
		cm_RequestMoveCredits(-1, gm_EntityIdField[*(unsigned short*) (u + 8) * 135], gm_ActiveTownIndex,
		    *(int*) (u + 0xac));
		if (--*(int*) (u + 0xb0) == 0) {
			he_FreeAction(u);
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		gm_AddTime(u + 0x52, 0x18, 0, 0);
		break;
	case -1:
	case -2:
		he_FreeAction(u);
		break;
	}
}
