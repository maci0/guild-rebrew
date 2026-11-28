#include "Develop/client_types.h"

extern Rec24_99f5a0 gm_DisasterState;

/* ADDRESS: GOLDTL 0x004fb630 */
void __cdecl gm_GetDisasterState(Rec24_99f5a0* p)
{
	*p = gm_DisasterState;
}
