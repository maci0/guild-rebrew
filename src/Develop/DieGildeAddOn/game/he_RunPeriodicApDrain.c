#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern char* g_14ad660;

void __cdecl he_FreeAction(char*);
void __cdecl he_RegisterApEvent(int, char*, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDTL 0x00551330 */
void __cdecl he_RunPeriodicApDrain(char* e)
{
	switch (*(int*) (e + 0x70)) {
	case -2:
	case -1:
		he_FreeAction(e);
		break;
	case 0:
		he_RegisterApEvent(*(unsigned short*) (e + 8), g_14ad660, -*(int*) (e + 0xac), 0);
		if (--*(int*) (e + 0xb0) == 0) {
			he_FreeAction(e);
			break;
		}
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
		break;
	}
}
