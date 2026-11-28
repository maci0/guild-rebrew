


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

char __cdecl d3sm_3D2SuperMap(int, float*, int*, int*, int*);
int __cdecl gm_FindBestBalancedTile(char*, int, int, int, int*, int*);
ent2c* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
int __cdecl cm_SendUpdateCutsceneEntitySlot(int, ent2c*);

/* ADDRESS: GOLDDE 0x004be7a0 */
int __cdecl cut_AssignGuardOrder(char* rec, char* e)
{
	int a;
	int b;
	ent2c l;
	ent2c* r;
	int c;
	int h;

	h = *(int*) (((char*)d3_ActiveScene) + 0xb0);
	if (d3sm_3D2SuperMap(h, (float*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c), &c, &a, &b) != 0 &&
	    gm_FindBestBalancedTile(e, c, a, 8, &c, &a) != 0) {
		r = gm_FindOrCreateEntitySlot(rec, e);
		r->fc = 0;
		l = *r;
		l.id = *(int*) (e + 4);
		l.f4 = 7;
		*(int*) l.name = c;
		*(int*) (l.name + 4) = a;
		return cm_SendUpdateCutsceneEntitySlot(*(int*) (rec + 0x10), &l);
	}
	return -1;
}
