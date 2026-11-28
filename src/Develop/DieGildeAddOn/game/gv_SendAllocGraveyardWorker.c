


#pragma pack(push, 1)
typedef struct
{
	int h0;
	int h4;
	int id;
	int x0c;
	char x10;
	int x11;
	int x15;
	char pad[3];
} GV_WORKER_ALLOC_MSG;
// SIZE 0x1c
#pragma pack(pop)

extern char* gm_CityEntity;
#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl gm_TryRecordCrime(int a, int b, int c, int d, int e);
int __cdecl cm_SendAllocGraveyardWorker(GV_WORKER_ALLOC_MSG* m);

/* ADDRESS: GOLDDE 0x004df340 */
int __cdecl gv_SendAllocGraveyardWorker(char* obj, int fieldId, int slotIndex, int workerId, int actionKind)
{
	GV_WORKER_ALLOC_MSG m;

	if (*(unsigned short*) (obj + 0x27) == 0xffff || *(unsigned short*) (obj + 0x27) == *((unsigned short*)gm_CityEntity) || slotIndex == -1) {
		return -1;
	}
	m.id = *(int*) (obj + 1);
	m.x0c = fieldId;
	m.x10 = (char) slotIndex;
	m.x11 = workerId;
	m.x15 = actionKind;
	gm_TryRecordCrime(0x1b, 1, ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (obj + 0x27)].entity_id, -1, *(int*) (obj + 1));
	return cm_SendAllocGraveyardWorker(&m);
}
