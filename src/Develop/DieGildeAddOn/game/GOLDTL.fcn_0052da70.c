#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;

// SIZE 0x21c
struct s_7f4ca0 {
	char pad[2];
	char kind;
	char pad2[0x51];
	int res;
	char pad3[0x1c4];
};

#include "Develop/DieGildeAddOn/game/entity_record.h"




void __cdecl d3_SelectSceneContext(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl fcn_00502cd0(int, int, int, int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl d3_VisitSceneObjects(int, char*, int, void*, char*);
char __cdecl d3_ApplyWimpelTextureCallback(char*, char*);
int __cdecl d3_GetContextIndex(int);
void __cdecl SelectTextureSet(char*, int, int, int);

void __cdecl d3_UpdateBuildingWimpelTextures(int idx)
{
	int save;
	struct s_7f4ca0* r;
	char* e;
	char* d;
	int n;

	save = d3_CurrentContextIndex;
	r = ((struct s_7f4ca0*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx]);
	d3_SelectSceneContext(0, 1);
	for (e = gm_StartFilteredEntitySearch(1, 4, idx); e != 0; e = gm_FindNextFilteredEntity()) {
		if (*(char**) (e + 0x61) != 0) {
			d3_VisitSceneObjects(g_67a370, *(char**) (e + 0x61), 0x340, (void*) d3_ApplyWimpelTextureCallback, e);
		}
	}
	for (e = fcn_00502cd0(0, 3, 7, 3, idx, 4, 0x1d); e != 0; e = gm_NextEntityQueryMatch()) {
		d = *(char**) (e + 0x3b);
		if (d != 0) {
			d3_SelectSceneContext(d3_GetContextIndex(*(int*) (d + 0x88)), 1);
			if (r != 0 && r->res != 0 && (r->kind == 5 || r->kind == 6 || r->kind == 7)) {
				n = r->res - 0x599;
				if (n != 0) {
					SelectTextureSet(**(char***) (d + 0x124),
					             *(int*) (**(char***) (d + 0x124) + 0x1cc), n, 1);
				}
			}
		}
	}
	d3_SelectSceneContext(save, 1);
}
