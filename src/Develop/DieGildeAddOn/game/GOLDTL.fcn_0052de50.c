#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x219];
};

extern char g_7f4ca0[];
extern char* gm_CityEntity;




void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_0052dd80(char*);
void __cdecl d3_CreateEntityFlagPennant(char*);

void __cdecl d3_RefreshBuildingPennants(void)
{
	int save;
	struct s_7f4ca0* r;
	char* e;

	save = d3_CurrentContextIndex;
	r = 0;
	d3_SelectSceneContext(0, 1);
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff) {
			r = ((struct s_7f4ca0 *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (e + 0x27)]);
		}
		if (r != 0 && r != ((struct s_7f4ca0*)gm_CityEntity) && (r->kind == 6 || r->kind == 7 || r->kind == 5) &&
		    (e[0x5a] & 1) == 0) {
			fcn_0052dd80(e);
			d3_CreateEntityFlagPennant(e);
		}
	}
	d3_SelectSceneContext(save, 1);
}
