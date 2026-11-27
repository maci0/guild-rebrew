#include "client_types.h"

#pragma pack(push, 1)







// SIZE 0xe
#pragma pack(pop)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"






extern pos14_7f4c00 gm_GameTime;


int __cdecl cm_GetCommandStatus(int id);
void __cdecl he_FreeAction(char* t);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl cm_SendSetHE(int a1, char* e);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl he_RegisterApEvent(int, char*, int, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl gm_IncreaseEntitySkill(ENTITY_RECORD* e, int v);

void __cdecl he_RunApTraitAction(char* t)
{
	char buf[0x100];
	ENTITY_RECORD* e;
	char* p;
	char* q;

	if (*(int*) (t + 0x70) == -2 || *(int*) (t + 0x70) == -1) {
		he_FreeAction(t);
		return;
	}
	if (t[0x78] & 4)
		return;
	if (*(int*) (t + 0x84) != -1 && cm_GetCommandStatus(*(int*) (t + 0x84)) == 0)
		return;
	*(int*) (t + 0x84) = -1;
	switch (*(int*) (t + 0x70)) {
	case 0:
		e = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (t + 8)]);
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*) &gm_GameTime);
			cm_SendSetHE(-1, t);
			return;
		}
		gm_IncreaseEntitySkill(e, *(unsigned char*) (t + 0xb8));
		gm_IncreaseEntitySkill(e, *(unsigned char*) (t + 0xb9));
		io_FormatTextBuffer(buf, 0x1a9e, e->entity_index);
		*(int*) (t + 0x70) = (unsigned char) (++t[0xba]) >= 5;
		*(short*) (t + 0x56) += 0x18;
		he_RegisterApEvent(*(unsigned short*) p, buf, 0, -*(int*) (t + 0xb4));
		return;
	case 1:
		e = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (t + 8)]);
		p = gm_LookupEntityRecordById(*(int*) (t + 0xac));
		if (p == 0) {
			*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*) &gm_GameTime);
			cm_SendSetHE(-1, t);
			return;
		}
		io_FormatTextBuffer(buf, 0x1a9f, e->entity_index);
		he_PostEntityMessage(*(int*) (p + 4), *(int*) (p + 4), buf, 0, 0x5f4, 0);
		q = (char*) gm_GetEntityTableEntry((char*) (p));
		if (q != 0) {
			(*(int*) (q + 0x64))++;
		}
		*(pos14_7f4c00*) (t + 0x52) = (*(pos14_7f4c00*) &gm_GameTime);
		cm_SendSetHE(-1, t);
		return;
	}
}
