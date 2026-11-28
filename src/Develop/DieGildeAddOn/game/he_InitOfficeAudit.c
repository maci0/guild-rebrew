#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_actions.h"

extern pos14_7f4c00 gm_GameTime;

extern void __cdecl gm_GenerateShuffledIndices(int a, void* p);


/* ADDRESS: GOLDTL 0x0055a040 */
void __cdecl he_InitOfficeAudit(char* action)
{
	int* p;
	int n;

	gm_GenerateShuffledIndices(6, action + 0xb0);
	p = (int*)(action + 0xb0);
	n = 6;
	do {
		*p = *p + 1;
		p++;
	} while (--n != 0);
	*(pos14_7f4c00*)(action + 0x52) = gm_GameTime;
	*(int*)(action + 0x70) = 0xc;
	*(short*)(action + 0x56) = 9;
	*(int*)(action + 0x58) = 0;
}
