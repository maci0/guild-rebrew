#include "Develop/Units/d3/d3_object.h"
extern int g_67a370;



#include <string.h>

#ifdef REBREW_GOLD
#define OFF_LIST_NEXT 0x1fc
#define OFF_OBJ_NEXT 0x1f0
#else
#define OFF_LIST_NEXT 0x200
#define OFF_OBJ_NEXT 0x1f4
#endif

// SIZE 0x84
struct list_514d80 {
	char* a[32];
	int n;
};

void __cdecl fcn_004379a0(int, int, int, void*, struct list_514d80*);
void __cdecl fcn_004458e0(char*, int);

char __cdecl fcn_00514d30(char*, struct list_514d80*);

void __cdecl fcn_00514d80(int x)
{
	struct list_514d80 l;
	char* o;
	char* next;
	int i;

	l.n = 0;
	fcn_004379a0(g_67a370, x, 0x2c0, (void*) fcn_00514d30, &l);
	for (i = 0; i < l.n; i++) {
		for (o = *(char**) (l.a[i] + OFF_LIST_NEXT); o != 0; o = next) {
			next = *(char**) (o + OFF_OBJ_NEXT);
			if (*(int*) (o + 0x218) >= 5 && strstr(o, "rLicht") != 0) {
				fcn_004458e0(o, x);
			}
		}
		d3_DestroyObject((D3_OBJECT*) (l.a[i]));
	}
}
