// FUNCTION: GOLD 0x00541460
// FUNCTION: GOLDTL 0x005492e0

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_005492e0(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	if (e[0x78] & 2) {
		fcn_004c5620(-1, e);
	}
}
