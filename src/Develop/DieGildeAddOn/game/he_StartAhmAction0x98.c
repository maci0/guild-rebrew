unsigned short __cdecl gm_RandomMod(int);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




int __cdecl cm_SendSetHE(int, char*);

void __cdecl he_StartAhmAction0x98(char* o)
{
	pos14_7f4c00* p;

	if (o[0x78] & 4) {
		return;
	}
	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	if (*(unsigned short*) (o + 0x56) > 0x13) {
		((pos14_7f4c00*) (o + 0x52))->a++;
		*(short*) (o + 0x56) = 0xd;
	} else if (*(unsigned short*) (o + 0x56) < 9) {
		*(short*) (o + 0x56) = gm_RandomMod(8) + 9;
	}
	*(int*) (o + 0xac) = 0;
	*(int*) (o + 0xb0) = -1;
	*(int*) (o + 0xb4) = -1;
	*(int*) (o + 0x84) = cm_SendSetHE(0, o);
}
