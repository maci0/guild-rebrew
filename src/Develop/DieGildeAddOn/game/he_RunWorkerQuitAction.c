// SIZE 0x21c
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_GetEntityRelation(int, int);
void __cdecl cm_RequestChangePlayerHe(int, int, int);
void __cdecl cm_RequestCancelEntityEvent(int);

int __cdecl cm_AppendCommandSyncField(unsigned char, unsigned char, short, void*);
void __cdecl cm_SendSetAttribute(void);
int __cdecl gm_FindFallbackPublicBuilding(char*, int*, int*);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
char* __cdecl gm_FindBuildingPrimarySlot(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x005666b0 */
/* Timed action 0x33 (HE_PERSONAL_KUENDIGEN) START: if the person still exists and is not
 * class 0x14, due = start; otherwise the action is freed. */
void __cdecl he_StartWorkerQuitAction(char* h)
{
	char* p;

	p = gm_LookupEntityRecordById(*(int*) (h + 0xac));
	if (p != 0 && p[2] != 0x14) {
		*(pos14_7f4c00*) (h + 0x52) = *(pos14_7f4c00*) (h + 0x44);
		return;
	}
	he_FreeAction(h);
}

void __cdecl he_RunWorkerQuitAction(char* u)
{
	int v;
	int a;
	int b;
	char text[0x400];
	char* h;
	char* q;

	v = 0;
	switch (*(int*) (u + 0x70)) {
	case 0:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h == 0 || *(char**) (h + 0x16c) == 0
		    || gm_GetEntityRelation(*(unsigned short*) (*(char**) (h + 0x16c) + 0x27), *(unsigned short*) h) > -0x1a) {
			goto kill;
		}
		cm_RequestChangePlayerHe(*(int*) (h + 4), 0, 0);
		cm_RequestCancelEntityEvent(*(int*) (h + 4));
		cm_BeginPacketFieldDelta(h, *(int*) (h + 4));
		cm_AppendCommandSyncField(4, 1, h - cm_PacketDeltaBase + 0x16c, &v);
		cm_SendSetAttribute();
		if (gm_FindFallbackPublicBuilding(h, &a, &b) != 0) {
			if (b != -1) {
				ch_StartMovement(*(int*) (h + 4), a, b, 0, 0, "Entlassen");
			} else {
				ch_StartMovement(*(int*) (h + 4), a, -1, 0, 1, "Entlassen");
			}
		}
		v = -5;
		cm_RequestCopyEntityData(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (*(char**) (h + 0x16c) + 0x27)])->entity_id, *(int*) (h + 4), v, 1);
		q = gm_FindBuildingPrimarySlot(*(char**) (h + 0x16c));
		io_FormatTextBuffer(text, 0x1bac, *(unsigned short*) h, *(char**) (h + 0x16c));
		if (q != 0) {
			h = *(char**) (h + 0x16c);
			he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (h + 0x27)])->entity_id, -1, text, 0, 0x5f2, *(int*) (h + 1), *(int*) (q + 2), 0,
			    "_NACHRICHTEN_HS_01");
		} else {
			he_PostEntityMessage(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[*(unsigned short*) (*(char**) (h + 0x16c) + 0x27)])->entity_id, -1, text, 0, 0x5f2, "_NACHRICHTEN_HS_01");
		}
		he_FreeAction(u);
		return;
	case -2:
	case -1:
kill:
		he_FreeAction(u);
		break;
	}
}
