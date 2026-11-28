extern int d3_ActiveScene;

// SIZE 0x84
struct list_55d630 {
	char* a[32];
	int n;
};



#include <string.h>

void __cdecl d3_VisitSceneObjects(int, char*, int, void*, struct list_55d630*);
char __cdecl he_CollectTransporterDummies(char*, struct list_55d630*);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDDE 0x00543840 */
char* __cdecl he_PickRandomTransporterDummy(char* o)
{
	struct list_55d630 l;
	int saved;

	memset(&l, 0, sizeof(l));
	l.n = 0;
	if (o != 0 && (o[0x214] & 1) == 0) {
		saved = *(int*) (o + 0x1f4);
		*(int*) (o + 0x1f4) = 0;
		d3_VisitSceneObjects(d3_ActiveScene, o, 0x100, (void*) he_CollectTransporterDummies, &l);
		*(int*) (o + 0x1f4) = saved;
	} else {
		d3_VisitSceneObjects(d3_ActiveScene, o, 0x100, (void*) he_CollectTransporterDummies, &l);
	}
	if (l.n == 0) {
		return 0;
	}
	return l.a[gm_RandomMod(l.n)];
}
