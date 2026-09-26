// FUNCTION: GOLD 0x0054cac0
// SIZE: 97
// FUNCTION: GOLDTL 0x00554b20
// SIZE: 97

typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_00554b20(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
		fcn_00500bb0(e + 0x52, 0x18, 0, 0);
		*(short*) (e + 0x56) = 9;
		*(int*) (e + 0x58) = 0;
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
