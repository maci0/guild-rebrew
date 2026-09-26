// FUNCTION: GOLD 0x00548540
// SIZE: 77
// FUNCTION: GOLDTL 0x005504f0
// SIZE: 77

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_005504f0(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	*(int*) (e + 0xb0) = *(int*) (e + 0xac) + 1;
	fcn_00500bb0(e + 0x52, 0x18, 0, 0);
}
