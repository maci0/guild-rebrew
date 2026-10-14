

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

void __cdecl fcn_00569a40(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 1, gm_RandomMod(0x1e) - 0x14, 0);
}
