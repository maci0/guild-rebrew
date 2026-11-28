#include "d2_capacity.h"
typedef struct HitObj {
	int f0;
	char pad4[0xc];
	int f10;
	int f14;
	int f18;
	int f1c;
	char pad20[0x10];
	int f30;
	int f34;
	char pad38[0x10];
	int f48;
	int f4c;
	char* f50;
	char pad54[0x34];
	int f88;
} HitObj;
/* SIZE 0x8c */

extern int g_67d388;
extern HitObj** d2_ZOrderStack;
#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x0046ac40 */
/* ADDRESS: GOLDDE 0x0045e430 */
int __cdecl d2_HitTestWindow(int x, int y)
{
	HitObj* o;
	int n;
	int hit;

	g_67d388 = -1;
	for (n = d2_ELEMENT_CAPACITY - 1; n >= 0; n--) {
		hit = 0;
		o = d2_ZOrderStack[n];
		if (o == 0) {
			continue;
		}
		if (o->f50 != 0) {
			hit = *(int*) (o->f50 + 0x198);
		}
		if (x < o->f10 || x > o->f10 + o->f18) {
			continue;
		}
		if (y < o->f14 || y > o->f14 + o->f1c) {
			continue;
		}
		if (hit != 0) {
			continue;
		}
		if (y < o->f30 || y > o->f34) {
			continue;
		}
		if (o->f4c != 0 || o->f48 != 0) {
			continue;
		}
		if (*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[o->f0].kind)) != 0x40) {
			continue;
		}
		g_67d388 = o->f88;
		break;
	}
	return g_67d388;
}
