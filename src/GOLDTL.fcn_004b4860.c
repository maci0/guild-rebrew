// FUNCTION: GOLD 0x004b46f0
// FUNCTION: GOLDTL 0x4b4860

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

unsigned char* __cdecl fcn_00503fe0(int, ...);
unsigned char* __cdecl fcn_00503e80(void);
int __cdecl fcn_00500d20(void*, void*);

int __cdecl fcn_004b4860(unsigned short* key, char* x)
{
	unsigned char* e;

	e = fcn_00503fe0(2, 4, key[0], 5, 2);
	while (e != 0) {
		if (*e >= 5 && *(int*) (e + 0x65) == *(int*) (key + 2) &&
		    fcn_00500d20(e + 0x69, ((char*)&g_7f4c00)) > *(int*) (x + 0x18))
			return 1;
		e = fcn_00503e80();
	}
	return 0;
}
