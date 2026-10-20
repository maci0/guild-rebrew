#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char* g_14ad660;

void __cdecl fcn_00546190(char*);
void __cdecl he_RegisterApEvent(int, char*, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDTL 0x00551330 */
void __cdecl fcn_00551330(char* e)
{
	switch (*(int*) (e + 0x70)) {
	case -2:
	case -1:
		fcn_00546190(e);
		break;
	case 0:
		he_RegisterApEvent(*(unsigned short*) (e + 8), g_14ad660, -*(int*) (e + 0xac), 0);
		if (--*(int*) (e + 0xb0) == 0) {
			fcn_00546190(e);
			break;
		}
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
		break;
	}
}
