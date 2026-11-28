#include <string.h>
#include "Develop/DieGildeAddOn/game/client_placement.h"

extern int d3_ActiveScene;
extern int d3_GfxDetails;

#ifdef REBREW_GOLD
char __cdecl d3_VisitSceneObjectsUntilStopped(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect fcn_0058fa00
#define lc_WalkScene d3_VisitSceneObjectsUntilStopped
#else
char __cdecl d3_VisitSceneObjects(char*, char*, unsigned int, char (__cdecl*)(char*, void*), void*);
#define lc_Collect lc_CollectVegetationObjects
#define lc_WalkScene d3_VisitSceneObjects
#endif
/* 0x442d50 / Gold 0x447300 keeps a numeric object context. */
char __cdecl d3_SetSubtreeVisible(int, unsigned char);

void __cdecl lc_SetVegetationVisible(char* node, int flag)
{
	LC_OBJECT_LIST list;
	int i;
	char* object;

	memset(&list, 0, sizeof(list));
	lc_WalkScene((char*) d3_ActiveScene, node, 0x2c0, lc_Collect, &list);
	for (i = 0; i < list.count; i++) {
		object = list.objects[i];
		if (flag != 0 && (i < (d3_GfxDetails & 0xff) || (char) d3_GfxDetails == 2)) {
			d3_SetSubtreeVisible((int) object, 1);
		}
		else {
			d3_SetSubtreeVisible((int) object, 0);
		}
	}
}
