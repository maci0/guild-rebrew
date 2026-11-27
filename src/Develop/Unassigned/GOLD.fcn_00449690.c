#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_VisitSceneObjectsUntilStopped(int, char*, int, void*, void*);
int __cdecl d3_MatchSceneObjectCallback(char*, char**);

/* Finds the child of o named name (and equal to ptr when ptr is given);
 * GOLDTL 0x445600 is the counterpart. */

/* ADDRESS: GOLD 0x00449690 */
char* __cdecl d3_FindSceneObjectGold(char* o, int flags, char* ptr, char* name)
{
	char* st[3];
	int saved;

	if (ptr == 0 && name == 0) {
		return 0;
	}
	st[1] = ptr;
	st[0] = name;
	st[2] = 0;
	if (o != 0) {
		saved = *(int*) (o + 0x1f0);
		*(int*) (o + 0x1f0) = 0;
	}
	d3_VisitSceneObjectsUntilStopped((int) g_5fb5b0, o, flags | 0x200, d3_MatchSceneObjectCallback, st);
	if (o != 0) {
		*(int*) (o + 0x1f0) = saved;
	}
	return st[2];
}
