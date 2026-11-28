


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"



// SIZE 0x8
typedef struct F8 {
	int mask;
	int b;
} F8;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

extern __int64 g_666018;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl cm_SendAllocCharacter(int, int, int, int, int, int, char*);
int __cdecl ai_FindEntityInFavorRange(ENTITY_RECORD* p, int kind, F8 f, int c, float r, int* out);

void __cdecl he_AllocPruegelAction(char* action)
{
	char* actor;
	char* target;
	int found;

	gm_LookupEntityRecordById(*(int*) (action + 0xb4));
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
	if (*(int*) (action + 0x10) == -1) {
		target = gm_StartFilteredEntitySearch(1, 5, 0x16);
		if (target != 0 || (target = gm_StartFilteredEntitySearch(1, 5, 0xf)) != 0) {
			*(int*) (action + 0x10) = *(int*) (target + 1);
		}
	}
	*(int*) (action + 0xc8) = -1;
	*(int*) (action + 0xcc) = cm_SendAllocCharacter(0x11, *(int*) (action + 0x10), -1, 0, 2, 0x154, "PRUEGEL");
	actor = gm_LookupEntityRecordById(*(int*) (action + 0xb4));
	if (*(char**) (actor + 0x170) != 0) {
		target = *(char**) (actor + 0x170);
	} else {
		target = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) actor);
	}
	if (target == 0) {
		if (ai_FindEntityInFavorRange(((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (action + 8)]), 6, (*(F8*)&g_666018), 0, 100.0f, &found) != 0) {
			target = gm_StartFilteredEntitySearch(1, 1, found);
		}
	}
	*(int*) (action + 0xd0) = *(int*) (target + 1);
}
