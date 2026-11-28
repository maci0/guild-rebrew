


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

void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl d3sm_SampleHeight(int, float*, int*, int*, int*);
ent2c* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
int __cdecl cm_SendUpdateCutsceneEntitySlot(int, ent2c*);

int __cdecl gm_IssueEscapeOrder(char* rec, char* e, char* obj)
{
	float v[4];
	ent2c l;
	ent2c* r;
	int h;
	int x;
	int y;
	int z;

	h = *(int*) (((char*)d3_ActiveScene) + 0xb0);
	if (obj == 0 || e == 0 || rec == 0)
		return -1;
	d3_TransformPoint(obj, obj + 0x4c, v);
	if (d3sm_SampleHeight(h, v, &x, &y, &z) == 0)
		return -1;
	r = gm_FindOrCreateEntitySlot(rec, e);
	if (r == 0)
		return -1;
	r->fc = 0;
	l = *r;
	l.id = *(int*) (e + 4);
	l.f4 = 3;
	*(int*) l.name = x;
	*(int*) (l.name + 4) = y;
	return cm_SendUpdateCutsceneEntitySlot(*(int*) (rec + 0x10), &l);
}
