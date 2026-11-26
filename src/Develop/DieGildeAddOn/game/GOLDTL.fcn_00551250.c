#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern int g_7f4ca4[];
extern unsigned char g_773d75;

void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_FreeAction(void*);

/* ADDRESS: GOLDTL 0x00551250 */
void __cdecl fcn_00551250(char* u)
{
	switch (*(int*) (u + 0x70)) {
	case 0:
		fcn_004c5150(-1, g_7f4ca4[*(unsigned short*) (u + 8) * 135], g_773d75,
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
