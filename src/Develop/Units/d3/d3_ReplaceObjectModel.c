#include "Develop/Units/d3/d3_object.h"


void __cdecl d3_DisposeObject(char*);
char* __cdecl d3_NextVisibleSceneNode(char*);

void __cdecl d3_LoadModel(int, int);
void __cdecl d3_AttachCachedModelParts(char*, int, int);
#include "Develop/Units/d3/client_scene_loader.h"

/* ADDRESS: GOLDDE 0x0043b1e0 */
char __cdecl d3_ReplaceObjectModel(char* o, int a2)
{
	char* p;
	char* n;

	if (o == 0) {
		return 0;
	}
	if (*(char**) (o + 0x200) != 0) {
		d3_DisposeObject(*(char**) (o + 0x200));
		*(char**) (o + 0x200) = 0;
	}
	p = *(char**) (o + 0x1f4);
	if (p != 0 && (p[0x214] & 1) == 0) {
		n = d3_NextVisibleSceneNode(o);
		d3_DisposeObject(p);
		*(char**) (o + 0x1f4) = n;
	}
	d3_CleanupObjectDrawData((D3_OBJECT*) (o));
	d3_LoadModel(a2, a2);
	d3_AttachCachedModelParts(o, 0, a2);
	d3_ReloadSceneTextureSurfaces(0);
	p = *(char**) (o + 0x1ec);
	if (p != 0 && *(int*) (p + 0x40c) != 0) {
		return 1;
	}
	return 0;
}
