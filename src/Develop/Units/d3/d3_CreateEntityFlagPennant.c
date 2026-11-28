extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/entity_record.h"
// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char gm_EntitySlotTable[];



void __cdecl d3_VisitSceneObjects(int, char*, int, void*, char*);
char __cdecl d3_CreatePennantAtFlagDummy(char*, char*);

/* ADDRESS: GOLDDE 0x00516360 */
void __cdecl d3_CreateEntityFlagPennant(char* e)
{
	char* o;
	int saved;
	char k;

	o = *(char**) (e + 0x61);
	if (o == 0) {
		return;
	}
	if (*(unsigned short*) (e + 0x27) == 0xffff) {
		return;
	}
	k = ((struct s_7f4ca0 *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (e + 0x27)])->kind;
	if (k == 6 || k == 7 || k == 5) {
		if ((o[0x214] & 1) == 0) {
			saved = *(int*) (o + 0x1f4);
			*(int*) (o + 0x1f4) = 0;
			d3_VisitSceneObjects(d3_ActiveScene, *(char**) (e + 0x61), 0x100, (void*) d3_CreatePennantAtFlagDummy, e);
			*(int*) (*(char**) (e + 0x61) + 0x1f4) = saved;
		} else {
			d3_VisitSceneObjects(d3_ActiveScene, o, 0x100, (void*) d3_CreatePennantAtFlagDummy, e);
		}
	}
}
