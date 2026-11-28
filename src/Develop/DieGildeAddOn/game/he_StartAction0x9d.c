int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);

void __cdecl he_StartAction0x9d(char* o)
{
	char* x;
	int id;

	*(int*) (o + 0x70) = 0;
	if (o[0x78] & 4) {
		return;
	}
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	x = gm_LookupEntityRecordById(*(int*) (o + 0xb0));
	if (x == 0) {
		*(int*) (o + 0x84) = cm_SendSetHE(-1, o);
		return;
	}
	if (*(char**) (x + 0x170) != 0) {
		id = *(int*) (*(char**) (x + 0x170) + 1);
	} else {
		id = -1;
	}
	gm_TryRecordCrime(0x1c, 1, *(int*) (o + 0xc), *(int*) (x + 4), id);
	*(int*) (o + 0x84) = cm_SendSetHE(0, o);
}
