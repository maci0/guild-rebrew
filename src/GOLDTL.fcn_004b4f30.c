// FUNCTION: GOLD 0x004b4dc0
// SIZE: 98
// FUNCTION: GOLDTL 0x4b4f30
// SIZE: 98

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

double __cdecl fcn_004fc460(float*);
int __cdecl fcn_004b52d0(int, int, int);

int __cdecl fcn_004b4f30(int a1, int a2, char* a3)
{
	float buf[10];

	if ((*(int*)&g_7f4c00) < 10)
		return 0;
	fcn_004fc460(buf);
	if (*(int*) (a3 + 0x14) < buf[6])
		return fcn_004b52d0(a2, 0, *(int*) (a3 + 0x18));
	return fcn_004b52d0(a2, 1, *(int*) (a3 + 0x18));
}
