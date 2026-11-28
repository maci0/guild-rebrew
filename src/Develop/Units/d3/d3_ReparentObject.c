#include "Develop/Units/d3/d3_object.h"
// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

// SIZE 0x40
typedef struct {
	float m[4][4];
} Mat;

// SIZE 0x38
typedef struct {
	char p0[0xc];
	char xc[0x2c];
} Slot;

typedef struct Ent Ent;

// SIZE 0x21c
struct Ent {
	char p0[0x4c];
	Vec3 pos;
	char p58[0x2c];
	Vec3 x84;
	char p90[0x158];
	Slot* slots;
	char p1ec[8];
	Ent* next;
	char p1f8[8];
	Ent* child;
	char p204[0x14];
	int kind;
};

int __cdecl d3_FindSceneObject(Ent*, int, Ent*, int);
void __cdecl d3_TransformPoint(Ent*, void*, Vec4*);
void __cdecl d3_SetObjectRotation(Ent*, void*);
void __cdecl d3_ComposeObserverMatrix(Ent*, char*, int, Mat*);

void __cdecl d3_RegisterSceneObjectTl(Ent*);
void __cdecl d3_AttachSceneNode(Ent*, Ent*);
void __cdecl d3_ApplyWorldTransformToObject(Ent*, Vec4*, Mat*);
void __cdecl d3_TransformWorldToParent(Ent*, Vec4*, Mat*, Slot*, char*);


/* ADDRESS: GOLDTL 0x004458e0 */
/* ADDRESS: GOLDDE 0x0043d670 */
char __cdecl d3_ReparentObject(Ent* e, Ent* parent)
{
	Vec3 v;
	Vec4 wpos;
	Mat wm;
	Vec4 tmp[7];
	Mat mats[7];
	Ent* p;
	int i;

	if (e == parent || e == 0) {
		return 0;
	}
	if (parent != 0) {
		for (p = parent->child; p != 0; p = p->next) {
			if (p == e) {
				return 1;
			}
		}
		if (d3_FindSceneObject(e, 0x1ff, parent, 0) != 0) {
			return 0;
		}
	}
	if (e->kind >= 5 && e->slots != 0) {
		v.x = e->x84.x;
		v.y = e->x84.y;
		v.z = e->x84.z;
		for (i = 0; i < 7; i++) {
			d3_TransformPoint(e, &e->slots[i], &tmp[i]);
			d3_SetObjectRotation(e, e->slots[i].xc);
			d3_ComposeObserverMatrix(e, 0, 1, &mats[i]);
		}
		d3_SetObjectRotation(e, &v);
	}
	d3_TransformPoint(e, &e->pos, &wpos);
	d3_ComposeObserverMatrix(e, 0, 1, &wm);
	d3_UnlinkObject((D3_OBJECT*) (e));
	if (parent == 0) {
		d3_RegisterSceneObjectTl(e);
	} else {
		d3_AttachSceneNode(parent, e);
	}
	d3_ApplyWorldTransformToObject(e, &wpos, &wm);
	if (e->kind >= 5 && e->slots != 0) {
		for (i = 0; i < 7; i++) {
			d3_TransformWorldToParent(e, &tmp[i], &mats[i], &e->slots[i], e->slots[i].xc);
		}
	}
	return 1;
}
