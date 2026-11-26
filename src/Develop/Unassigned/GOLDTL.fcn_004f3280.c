


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
} Msg1c;
// SIZE 0x1c
#pragma pack(pop)

extern char* gm_CityEntity;
#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl gm_TryRecordCrime(int a, int b, int c, int d, int e);
int __cdecl cm_SendAllocGraveyardWorker(Msg1c* m);

int __cdecl fcn_004f3280(char* obj, int a2, int a3, int a4, int a5)
{
	Msg1c m;

	if (*(unsigned short*) (obj + 0x27) == 0xffff || *(unsigned short*) (obj + 0x27) == *((unsigned short*)gm_CityEntity) || a3 == -1) {
		return -1;
	}
	m.id = *(int*) (obj + 1);
	m.x0c = a2;
	m.x10 = (char) a3;
	m.x11 = a4;
	m.x15 = a5;
	gm_TryRecordCrime(0x1b, 1, ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (obj + 0x27)].entity_id, -1, *(int*) (obj + 1));
	return cm_SendAllocGraveyardWorker(&m);
}
