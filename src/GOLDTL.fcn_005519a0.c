int __cdecl fcn_004c5620(int, char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

void __cdecl fcn_005519a0(char* o)
{
	char* p;

	for (p = fcn_005463a0(2, 0, 0x5f, 2, *(unsigned short*) (o + 8)); p != 0; p = fcn_005462a0()) {
		if (p != o) {
			*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
			*(int*) (o + 0x84) = fcn_004c5620(-1, o);
			return;
		}
	}
	*(int*) (o + 0x70) = 0;
	o[0xba] = 0;
}
