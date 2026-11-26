


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl fcn_004c4450(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_HandleAction0x4b(char* u)
{
	if (*(int*) (u + 0x84) != -1 && fcn_004c4450(*(int*) (u + 0x84)) == 0) {
		return;
	}
	*(int*) (u + 0x84) = -1;
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (u[0x78] & 2) {
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 2, 0);
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
		}
		break;
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	}
}
