

#include <string.h>

typedef struct
{
	int tag;
	int id;
	int x8;
	int xc;
	int x10;
	int x14;
} Msg18;
// SIZE 0x18

int __cdecl ahm_CheckFlag(char* p);
int __cdecl ahm_FindRecipeSlot(char* p, int id);
int __cdecl cm_RequestAhmCommand(Msg18* m);

int __cdecl ahm_RequestSlotClearMatch(char* entity, int recipeId)
{
	Msg18 m;

	if (!ahm_CheckFlag(entity)) {
		return -1;
	}
	if (!ahm_FindRecipeSlot(entity, recipeId)) {
		return -1;
	}
	memset(&m, 0, sizeof(m));
	m.tag = 0x61736452;
	m.id = *(int*) (entity + 4);
	m.x8 = recipeId;
	return cm_RequestAhmCommand(&m);
}
