#include "Develop/Units/d3/d3_object.h"
extern int d3_ActiveScene;



#include <string.h>

#ifdef REBREW_GOLD
#define OFF_LIST_NEXT 0x1fc
#define OFF_OBJ_NEXT 0x1f0
#else
#define OFF_LIST_NEXT 0x200
#define OFF_OBJ_NEXT 0x1f4
#endif

// SIZE 0x84
struct FACKEL_OBJ_LIST {
	char* a[32];
	int n;
};

void __cdecl d3_VisitSceneObjects(int, int, int, void*, struct FACKEL_OBJ_LIST*);
void __cdecl d3_ReparentObject(char*, int);

char __cdecl d3_CollectFackelObjects(char*, struct FACKEL_OBJ_LIST*);

/* ADDRESS: GOLDDE 0x004ff7f0 */
void __cdecl d3_ReparentFackelLights(int x)
{
	struct FACKEL_OBJ_LIST l;
	char* o;
	char* next;
	int i;

	l.n = 0;
	d3_VisitSceneObjects(d3_ActiveScene, x, 0x2c0, (void*) d3_CollectFackelObjects, &l);
	for (i = 0; i < l.n; i++) {
		for (o = *(char**) (l.a[i] + OFF_LIST_NEXT); o != 0; o = next) {
			next = *(char**) (o + OFF_OBJ_NEXT);
			if (*(int*) (o + 0x218) >= 5 && strstr(o, "rLicht") != 0) {
				d3_ReparentObject(o, x);
			}
		}
		d3_DestroyObject((D3_OBJECT*) (l.a[i]));
	}
}
