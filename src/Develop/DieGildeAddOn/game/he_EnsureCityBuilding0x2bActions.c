extern char* gm_CityEntity;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};




#include <string.h>

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl cm_SendCopyEntityData(struct msg*);

/* ADDRESS: GOLDDE 0x0052d7b0 */
void __cdecl he_EnsureCityBuilding0x2bActions(void)
{
	struct msg m;
	char* e;
	char* p;
	int found;

	found = 0;
	memset(&m, 0, sizeof(m));
	for (e = gm_StartFilteredEntitySearch(1, 5, 7); e != 0; e = gm_FindNextFilteredEntity()) {
		for (p = he_StartHandlungSearch(1, 0, 0x2b); p != 0; p = he_fn_Handlung()) {
			if (*(int*) (p + 0x10) == *(int*) (e + 1)) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			m.b4 = 0x2b;
			m.pos = gm_GameTime;
			m.b36 = 2;
			m.f8 = *(int*) (gm_CityEntity + 4);
			m.fc = *(int*) (e + 1);
			m.b5c = 0;
			cm_SendCopyEntityData(&m);
		}
	}
}
