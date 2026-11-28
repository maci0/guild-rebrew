#include "Develop/client_types.h"
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 gm_GameTime;


/* ADDRESS: GOLDTL 0x0056b680 */
void __cdecl he_StartUeberfall(char* o)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (o + 0x52);
	*p = gm_GameTime;
	*(pos14_7f4c00*) (o + 0xcc) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0xcc), 0x30, 0, 0);
	gm_AddTime(p, 0, 0, 1);
}
