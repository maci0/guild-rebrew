#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct
{
	int id;
	char pad[0x40];
} Rec44;
// SIZE 0x44

extern unsigned char* lpGebaeudePROT;

int __cdecl cm_GetBuildingStatCount(unsigned char* e);
unsigned short __cdecl gm_RandomMod(unsigned short n);

Rec44* __cdecl gv_PickRandomFieldEntry(unsigned char* e)
{
	BUILDING_PROTOTYPE *ent;
	char* d;
	Rec44* recs;
	int n;
	int k;
	int idx;

	ent = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e];
	d = *(char**) (e + 0x65);
	if (ent->category == 0x1d && ent->level >= 1 && ent->level <= 3) {
		n = cm_GetBuildingStatCount(e);
		idx = gm_RandomMod((unsigned short) n);
		k = n;
		if (k != 0) {
			recs = *(Rec44**) (d + 0x20);
			while (k != 0) {
				if (recs[idx].id != -1) {
					return &recs[idx];
				}
				k--;
				idx = (idx + 1) % n;
			}
		}
	}
	return 0;
}
