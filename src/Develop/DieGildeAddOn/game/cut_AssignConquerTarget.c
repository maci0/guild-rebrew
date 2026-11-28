


#include <string.h>

typedef struct {
	int id;
	int f4;
	int f8;
	char fc;
	char padd[3];
	char name[0x10];
	int f20;
	int f24;
	int f28;
} ent2c;
// SIZE 0x2c

extern int d3_ActiveScene;

void __cdecl gm_GetEquippedCombatGear(char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl d3sm_3D2SuperMap(int, float*, int*, int*, int*);
ent2c* __cdecl gm_FindOrCreateEntitySlot(char*, char*);

int __cdecl cut_AssignConquerTarget(char* rec, char* e, char* obj)
{
	float v[4];
	ent2c* r;
	int h;
	int a;
	int b;
	int c;

	h = *(int*) (((char*)d3_ActiveScene) + 0xb0);
	gm_GetEquippedCombatGear(e);
	d3_TransformPoint(obj, obj + 0x4c, v);
	if (d3sm_3D2SuperMap(h, v, &c, &a, &b) == 0)
		return 0;
	r = gm_FindOrCreateEntitySlot(rec, e);
	r->fc = 0;
	strcpy(r->name, obj);
	r->id = *(int*) (e + 4);
	r->f4 = 4;
	r->f20 = c;
	r->f24 = a;
	return 1;
}
