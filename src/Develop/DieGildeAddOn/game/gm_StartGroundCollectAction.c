

typedef struct {
	int v[9];
} blk24;
// SIZE 0x24

extern blk24 g_68bef4;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl d3_FindSceneObject(int, int, int, int*);
char* __cdecl ch_CreateQueuedAction(int, void*, int, int, int);
void __cdecl cut_CollectGroundItem(void);

/* ADDRESS: GOLD 0x004d7000 */
void __cdecl gm_StartGroundCollectAction(int* args)
{
	char* e;
	unsigned short* s;
	char* p;
	char* o;

	if (args[1] == 0 || args[0] == -1)
		return;
	e = gm_LookupEntityRecordIn32SlotTable(args[0]);
	s = *(unsigned short**) (e + 0x16c);
	ch_CancelActionQueue((char*) *(int*) (e + 0x184));
	p = d3_FindSceneObject(0, 0x40, 0, args + 4);
	if (p == 0)
		return;
#ifdef REBREW_GOLD
	*(int*) (*(char**) (p + 0x200) + 0xa) = *s;
#else
	*(int*) (*(char**) (p + 0x204) + 0xa) = *s;
#endif
	o = ch_CreateQueuedAction(*(int*) (e + 0x184), cut_CollectGroundItem, 5, 0x2e, 1);
	*(char**) (o + 0x17c) = e;
	*(char**) (o + 0x180) = p;
	*(blk24*) (o + 0xf0) = g_68bef4;
}
