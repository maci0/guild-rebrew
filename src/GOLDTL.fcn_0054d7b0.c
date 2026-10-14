


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

int __cdecl gm_RandomMod(int);

void __cdecl fcn_0054d7b0(char* e)
{
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
	*(short*) (e + 0x56) = gm_RandomMod(10) + 10;
	*(int*) (e + 0x58) = (unsigned short) gm_RandomMod(0x3b);
	*(int*) (e + 0x5c) = 0;
}
