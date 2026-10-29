


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00500d20(void*, void*);

int __cdecl fcn_004b4860(unsigned short* key, char* x)
{
	unsigned char* e;

	e = gm_StartFilteredEntitySearch(2, 4, key[0], 5, 2);
	while (e != 0) {
		if (*e >= 5 && *(int*) (e + 0x65) == *(int*) (key + 2) &&
		    fcn_00500d20(e + 0x69, ((char*)&g_7f4c00)) > *(int*) (x + 0x18))
			return 1;
		e = gm_FindNextFilteredEntity();
	}
	return 0;
}
