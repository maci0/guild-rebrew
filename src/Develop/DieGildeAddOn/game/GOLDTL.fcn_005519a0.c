int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

void __cdecl fcn_005519a0(char* o)
{
	char* p;

	for (p = he_StartHandlungSearch(2, 0, 0x5f, 2, *(unsigned short*) (o + 8)); p != 0; p = he_fn_Handlung()) {
		if (p != o) {
			*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
			*(int*) (o + 0x84) = fcn_004c5620(-1, o);
			return;
		}
	}
	*(int*) (o + 0x70) = 0;
	o[0xba] = 0;
}
