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




void __cdecl fcn_004432d0(int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_0052dd80(char*);
void __cdecl fcn_0052d9d0(char*);

void __cdecl fcn_0052de50(void)
{
	int save;
	struct s_7f4ca0* r;
	char* e;

	save = d3_CurrentContextIndex;
	r = 0;
	fcn_004432d0(0, 1);
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		if (*(unsigned short*) (e + 0x27) != 0xffff) {
			r = ((struct s_7f4ca0 *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (e + 0x27)]);
		}
		if (r != 0 && r != ((struct s_7f4ca0*)gm_CityEntity) && (r->kind == 6 || r->kind == 7 || r->kind == 5) &&
		    (e[0x5a] & 1) == 0) {
			fcn_0052dd80(e);
			fcn_0052d9d0(e);
		}
	}
	fcn_004432d0(save, 1);
}
