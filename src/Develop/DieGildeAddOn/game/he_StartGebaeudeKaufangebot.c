#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

int __cdecl gm_SearchTable67(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x005643e0 */
/* ADDRESS: GOLDDE 0x0054a590 */
void __cdecl he_StartGebaeudeKaufangebot(char* e)
{
	char* p;
	pos14_7f4c00* q;

	p = (char*) gm_SearchTable67(*(int*) (e + 0xac));
	q = (pos14_7f4c00*) (e + 0x52);
	*q = gm_GameTime;
	gm_AddTime(q, 0, gm_RandomMod(0xa) + 0xa, 0);
	cm_RequestChangeBits(*(int*) (p + 1), 0x5a, 2, 0x200, 0);
}
