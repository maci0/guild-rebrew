extern char g_68d6f8[];
#include <string.h>
#include "Develop/Units/d3/d3_object.h"
#include "Develop/DieGildeAddOn/game/client_placement.h"

/* ADDRESS: GOLDDE 0x0057da80 */
char __cdecl lc_CollectVegetationObjects(char* obj, void* list)
{
	D3_OBJECT* parent;

	if (strstr(obj, (void*) &g_68d6f8) != 0) {
		parent = ((D3_OBJECT*) obj)->eltern;
		if (parent == 0 || parent->unbekannt_220 != 1) {
			((LC_OBJECT_LIST*) list)->objects[((LC_OBJECT_LIST*) list)->count] = obj;
			((LC_OBJECT_LIST*) list)->count = ((LC_OBJECT_LIST*) list)->count + 1;
		}
	}
	return ((LC_OBJECT_LIST*) list)->count < 0x20;
}
