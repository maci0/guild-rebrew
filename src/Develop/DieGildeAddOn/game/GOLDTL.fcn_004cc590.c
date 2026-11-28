struct ALLOC_CHAR_RECORD {
	char pad0[2];
	char kind;
	char pad3;
	int id;
	char pad8[0x164];
	int owner;
	char pad170[0xac];
};
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int nt_ClientSocket;
extern int gm_NextEntityId;
extern int cm_LastEntityId;
extern int(__stdcall* imp_timeGetTime)(void);

void __cdecl srv_SeedRandom(int);
int __cdecl cm_ResolveSpecialEntityId(unsigned char*, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned short __cdecl fcn_0050a7e0(int, int, int, int, int, int, int, int);
char* __cdecl gm_FindRecordById(int);
void __cdecl init_SpawnBuildingCharacter(int, int, int, int, int);
char* __cdecl gm_AllocObjekt(int, int, int);
void __cdecl ch_UpdateHeldObjectAttachment(struct ALLOC_CHAR_RECORD*);


/* ADDRESS: GOLDTL 0x004cc590 */
int __cdecl fcn_004cc590(unsigned char* request, char* response)
{
	char* e;
	char* r;
	int id;

	if (nt_ClientSocket != -1)
		gm_NextEntityId = *(int*) (request + 0x10);
	else
		*(int*) (request + 0x22) = imp_timeGetTime();
	if (response != 0) {
		response[0] = 2;
		response[1] = 1;
		*(int*) (response + 6) = 0;
	}
	srv_SeedRandom(*(int*) (request + 0x22));
	if (*(int*) (request + 0x17) == -1) {
		e = 0;
	} else {
		*(int*) (request + 0x17) = cm_ResolveSpecialEntityId(request, *(int*) (request + 0x17));
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (request + 0x17));
		if (e == 0)
			return 1;
	}
	id = fcn_0050a7e0(request[0x14], -1, -1, 0x14, 0, request[0x1f], request[0x20], 0);
	if (id == 0xffff)
		return 1;
	if (*(int*) (request + 0x1b) != -1 && (r = gm_FindRecordById(*(int*) (request + 0x1b))) != 0)
		init_SpawnBuildingCharacter((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), *(int*) (e + 1), *(int*) (r + 2), 0, 0);
	else
		init_SpawnBuildingCharacter((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), *(int*) (e + 1), -1, 0, 0);
	(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].ptr_16c) = 0;
	(*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_type) = 0xd;
	if (request[0x21] != 0) {
		gm_AllocObjekt((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), request[0x21], 1);
		ch_UpdateHeldObjectAttachment(((struct ALLOC_CHAR_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id]));
	}
	cm_LastEntityId = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id);
	if (response != 0) {
		response[0] = 1;
		response[1] = 1;
		*(struct ALLOC_CHAR_RECORD**) (response + 6) = ((struct ALLOC_CHAR_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id]);
	}
	return 0;
}
