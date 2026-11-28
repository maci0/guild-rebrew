





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00547450 */
void __cdecl he_RunAction0x17(char* e)
{
	switch (*(int*) (e + 0x70)) {
	case 3:
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		gm_AddTime(e + 0x52, 0, 1, 0);
		break;
	case 9:
		he_FreeAction(e);
		break;
	}
}
