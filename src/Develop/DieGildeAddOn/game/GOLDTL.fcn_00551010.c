#include "client_types.h"

int __cdecl gm_RandomMod(unsigned short);
struct unit;
void __cdecl fcn_00546190(struct unit*);

/* ADDRESS: GOLDTL 0x00551010 */
void __cdecl fcn_00551010(char* u)
{
	*(pos14_7f4c00*) (u + 0x52) = *(pos14_7f4c00*) (u + 0x44);
	if ((unsigned short) gm_RandomMod(2) != 0) {
		fcn_00546190((struct unit*) u);
	}
}
