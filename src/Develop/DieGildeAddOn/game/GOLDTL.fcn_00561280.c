





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00561280(char* e)
{
	switch (*(int*) (e + 0x70)) {
	case 3:
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		fcn_00500bb0(e + 0x52, 0, 1, 0);
		break;
	case 9:
		fcn_00546190(e);
		break;
	}
}
