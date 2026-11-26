#include "client_types.h"


// SIZE 0xe

typedef struct {
	char pad0[0x8];
	pos14_7f4c00 when;
	char pad16[0x2];
	int f18;
	int f1c;
	char f20;
} fcn_004b3c00_rec;


extern pos14_7f4c00 gm_GameTime;

fcn_004b3c00_rec* __cdecl gm_FindMissionByEntityId(int);


/* ADDRESS: GOLDTL 0x004b3c00 */
fcn_004b3c00_rec* __cdecl fcn_004b3c00(int a)
{
	fcn_004b3c00_rec* p;

	p = gm_FindMissionByEntityId(a);
	if (p != 0) {
		p->when = (*(pos14_7f4c00*)&gm_GameTime);
		p->f18 = 0;
		p->f1c = 0;
		p->f20 = 0;
	}
	return p;
}
