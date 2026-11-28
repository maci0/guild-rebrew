


typedef struct {
	int v[9];
} blk24;
// SIZE 0x24

extern blk24 ch_PickupAnimName;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl d3_FindSceneObject(int, int, int, int*);
void __cdecl d3_ApplyWorldTransformToObject(int, char*, char*);
void __cdecl d3_SetObjectVisible(int, int);
char* __cdecl ch_CreateAction(int, int, int);

/* ADDRESS: GOLDDE 0x004c53f0 */
void __cdecl gm_StartGroundPickupAnimation(int* a)
{
	char* e;
	char* q;
	char* o;
	int h;

	if (a[1] == 0 || a[0] == -1)
		return;
	e = gm_LookupEntityRecordIn32SlotTable(a[0]);
	ch_CancelActionQueue((char*) *(int*) (e + 0x184));
	d3_FindSceneObject(0, 0x40, 0, a + 4);
	h = *(int*) (e + 0x1ac);
	if (h != 0) {
		q = *(char**) (*(char**) (e + 0x184) + 0x34);
		d3_ApplyWorldTransformToObject(h, q + 0x4c, q + 0x18c);
		d3_SetObjectVisible(h, 1);
		*(int*) (e + 0x1ac) = 0;
	}
	o = ch_CreateAction(*(int*) (e + 0x184), 0x2e, 1);
	*(blk24*) (o + 0xf0) = ch_PickupAnimName;
}
