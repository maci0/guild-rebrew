extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


int sprintf(char*, const char*, ...);
void __cdecl d3_SetSubtreeVisible(char*, int);
void __cdecl d3_ResolveSceneObjectProtoId(char*);
void __cdecl fcn_005107f0(void);

void __cdecl d3_BindEntitySceneObject(char* obj, unsigned char* ent, int kind)
{
	unsigned char* t;
	void** p;

	switch (kind) {
	case 2:
		t = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*ent];
		sprintf(obj, "gb_%s", t + 1);
		*(char**) (ent + 0x61) = obj;
		if ((((BUILDING_PROTOTYPE*)t)->category) != 10) {
			*(int*) (obj + 0x220) = 3;
			if (*(int*) (obj + 0x218) == 1 && (ent[0x5a] & 1) == 0) {
				d3_SetSubtreeVisible(obj, 1);
			}
		} else {
			*(int*) (obj + 0x220) = 0;
			*(int*) (obj + 0x224) = 0;
		}
		break;
	case 1:
		sprintf(obj, "ob_%s", ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) ent]) + 1);
		*(int*) (obj + 0x220) = 4;
		break;
	}
	d3_ResolveSceneObjectProtoId(obj);
	*(unsigned char**) (obj + 0x204) = ent;
	p = *(void***) (obj + 0x1ec);
	if (p != 0) {
		*p = (void*) fcn_005107f0;
	}
}
