#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

int __cdecl gm_SearchTable67(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x005643e0 */
void __cdecl fcn_005643e0(char* e)
{
	char* p;
	pos14_7f4c00* q;

	p = (char*) gm_SearchTable67(*(int*) (e + 0xac));
	q = (pos14_7f4c00*) (e + 0x52);
	*q = g_7f4c00;
	fcn_00500bb0(q, 0, gm_RandomMod(0xa) + 0xa, 0);
	fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0x200, 0);
}
