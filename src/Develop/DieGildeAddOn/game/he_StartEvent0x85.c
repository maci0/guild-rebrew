





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDDE 0x00556330 */
void __cdecl he_StartEvent0x85(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (e + 0x56) = 7;
	*(int*) (e + 0x58) = 0;
}
