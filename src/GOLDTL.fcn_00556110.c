// FUNCTION: GOLD 0x0054e0b0
// FUNCTION: GOLDTL 0x00556110

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00556110(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
		*(int*) (e + 0xac) = 0;
		*(int*) (e + 0xb0) = 0;
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
