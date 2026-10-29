#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_004c4dc0(void*, int);

char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_00502e30(char*, int);


/* ADDRESS: GOLDTL 0x004c8920 */
int __cdecl fcn_004c8920(char* a1, char* a2)
{
	char* f;
	char* e;

	*(int*) (a1 + 0x10) = fcn_004c4dc0(a1, *(int*) (a1 + 0x10));
	if (gm_ResolveEntityById(0, (void**) (&f), 0, *(int*) (a1 + 0x10)) == 0)
		return 1;
	if (*(short*) f != 0x2a && *(short*) f != 0x116)
		return 1;
	e = fcn_00502cd0(*(int*) (f + 0x14), 1, 0, *(unsigned short*) (a1 + 0x14));
	if (e == 0)
		return 1;
	if (*(int*) (e + 0xe) != 1)
		return 1;
	fcn_00502e30(f + 0x14, *(unsigned short*) (a1 + 0x14));
	if (a2 != 0)
		*a2 = 1;
	return 0;
}
