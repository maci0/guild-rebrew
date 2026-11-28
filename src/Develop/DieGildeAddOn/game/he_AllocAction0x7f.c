unsigned short __cdecl gm_RandomMod(int);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x0055a540 */
/* ADDRESS: GOLDDE 0x00540830 */
void __cdecl he_AllocAction0x7f(char* o)
{
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	*(short*) (o + 0x56) = gm_RandomMod(3) + 9;
	*(int*) (o + 0x58) = gm_RandomMod(4) * 15;
	*(int*) (o + 0xb0) = 0;
}
