#include "Develop/client_types.h"








extern pos14_7f4c00 gm_GameTime;
void __cdecl gm_AddTime(char*, int, int, int);

/* ADDRESS: GOLDTL 0x005530d0 */
/* ADDRESS: GOLDDE 0x00539480 */
void __cdecl he_StartSchutzgeldDialog(char* obj)
{
	pos14_7f4c00* p;

	p = (pos14_7f4c00*) (obj + 0x52);
	*p = gm_GameTime;
	gm_AddTime((char*) p, 0, 2, 0);
}
