#include "Develop/client_types.h"


// SIZE 0xe

typedef struct {
	char pad0[0x8];
	pos14_7f4c00 when;
	char pad16[0x2];
	int f18;
	int f1c;
	char f20;
} MISSION_RECORD;


extern pos14_7f4c00 gm_GameTime;

MISSION_RECORD* __cdecl gm_FindMissionByEntityId(int);


/* ADDRESS: GOLDTL 0x004b3c00 */
/* ADDRESS: GOLDDE 0x004a1ef0 */
MISSION_RECORD* __cdecl gm_ResetMissionEntry(int a)
{
	MISSION_RECORD* p;

	p = gm_FindMissionByEntityId(a);
	if (p != 0) {
		p->when = (*(pos14_7f4c00*)&gm_GameTime);
		p->f18 = 0;
		p->f1c = 0;
		p->f20 = 0;
	}
	return p;
}
