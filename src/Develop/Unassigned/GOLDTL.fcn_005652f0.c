





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);

void __cdecl fcn_005652f0(char* e)
{
	char* r;

	gm_LookupEntityRecordById(*(int*) (e + 0xac));
	r = he_StartHandlungSearch(2, 2, *(unsigned short*) (e + 8), 0, 0x25);
	if (r != 0) {
		*(int*) (r + 0x70) = -1;
	}
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
}
