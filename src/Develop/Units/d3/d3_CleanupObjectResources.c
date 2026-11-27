#include "Develop/Units/d3/d3_object.h"


void __cdecl d3_VisitSceneObjects(int, int, int, void*, char*);
void __cdecl d3_ClearMatchingAuxSlot(void);



void __cdecl d3_CleanupObjectResources(char* o)
{
	int h;

	if (o == 0) {
		return;
	}
	h = *(int*) (o + 0x20c);
	if (*(int*) (o + 0x218) == 1 && *(int*) (o + 0x21c) != 1) {
		*(int*) (o + 0x218) = *(int*) (o + 0x21c);
	}
	if (*(int*) (o + 0x218) == 8) {
		d3_VisitSceneObjects(h, 0, 0x40, d3_ClearMatchingAuxSlot, o);
	}
	if ((o[0x215] & 1) != 0) {
		d3_CleanupObjectAuxSlots((D3_OBJECT*) (o));
	}
	d3_CleanupObjectDrawData((D3_OBJECT*) (o));
}
