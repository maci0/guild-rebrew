


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;

extern int g_7747f0;
extern char g_774964;
extern char* g_773d78;
extern char g_6b5c60[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
unsigned short __cdecl gm_RandomMod(int);
char* __cdecl fcn_005049a0(char*);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_00526920(char*, int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl fcn_005703b0(char* u)
{
	char* list[0x40];
	int n;
	char* e;
	char* p;

	n = 0;
	if (g_7747f0 == 0) {
		*(int*) (u + 0x70) = -1;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (g_774964 != 0) {
			((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (u + 8)].entity_state = 5;
			(*(int*) (u + 0x70))++;
		}
		break;
	case 1:
		if (g_7f4c04 >= 0x16) {
			(*(int*) (u + 0x70))++;
			break;
		}
		for (e = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (u + 8)); e != 0 && n < 0x40; e = gm_FindNextFilteredEntity()) {
			list[n++] = e;
		}
		list[n++] = g_773d78;
		if (n != 0) {
			p = list[gm_RandomMod(n)];
			if (gm_RandomMod(4) != 0 && p != g_773d78 && ((e = fcn_005049a0(p)) != 0 || (e = gm_SetupEntityQuery(p)) != 0)) {
				fcn_00526920(p, *(int*) (e + 2), g_6b5c60);
			} else {
				fcn_00526920(p, -1, g_6b5c60);
			}
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		*(short*) (u + 0x56) += gm_RandomMod(2);
		*(int*) (u + 0x58) = gm_RandomMod(0x3c);
		break;
	case 2:
		((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (u + 8)].entity_state = 6;
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	}
}
