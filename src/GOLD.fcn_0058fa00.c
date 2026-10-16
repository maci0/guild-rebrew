#include "Develop/Units/d3/d3_object.h"
#include "client_placement.h"

int __cdecl fcn_0064d470(char*, void*);

/* ADDRESS: GOLD 0x0058fa00 */
char __cdecl fcn_0058fa00(char* obj, void* list)
{
	D3_OBJECT* parent;

	if (fcn_0064d470(obj, (void*) 0x60ea3c) != 0) {
		parent = ((D3_OBJECT*) obj)->eltern;
		if (parent == 0 || parent->unbekannt_220 != 1) {
			((LC_OBJECT_LIST*) list)->objects[((LC_OBJECT_LIST*) list)->count] = obj;
			((LC_OBJECT_LIST*) list)->count = ((LC_OBJECT_LIST*) list)->count + 1;
		}
	}
	return ((LC_OBJECT_LIST*) list)->count < 0x20;
}
