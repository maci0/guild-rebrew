#include "Develop/DieGildeAddOn/game/spiel.h"
// SIZE 0xe
#include "Develop/DieGildeAddOn/game/building_prototype.h"
// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
extern unsigned char* lpGebaeudePROT;

int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);

void __cdecl cm_AppendPacketFieldValue(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
char* __cdecl gm_FindBuildingOwner(unsigned char*);
char* __cdecl gm_FindBuildingPrimarySlot(unsigned char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x0055fd10 */
void __cdecl he_RunBuildingExpansion(char* u)
{
	char* h;
	int v;
	char text[0x400];
	unsigned char* p;
	BUILDING_PROTOTYPE* t;
	char* r;
	char* w;
	int a;
	int b;
	int off;
	int msg;

	switch (*(int*) (u + 0x70)) {
	case 0:
		*(int*) (u + 0x70) += 1;
		return;
	case 1:
		if (gm_CompareGameTime((pos14_7f4c00*) (u + 0x52), &gm_GameTime) >= 0) {
			return;
		}
		gm_ResolveEntityById(0, (void**) (&h), 0, *(int*) (u + 0xac));
		if (h == 0) {
			goto kill;
		}
		v = 1;
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
		if (p == 0) {
			goto kill;
		}
		t = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*p];
		if (*(short*) h != 0x116) {
			a = t->dimension_240;
			b = t->dimension_241;
		} else {
			a = b = t->dimension_242;
		}
		if (*(int*) (u + 0xb0) > 0) {
			*(int*) (u + 0xb0) -= 1;
			if (*(unsigned char*) (h + 0x1c) < a) {
				cm_BeginPacketFieldDelta(h, *(int*) (h + 2));
				off = h - cm_PacketDeltaBase + 0x1c;
				cm_AppendPacketFieldValue(1, 1, off, &v);
				cm_RequestChangeAttribute();
			}
		} else if (*(int*) (u + 0xb4) > 0) {
			*(int*) (u + 0xb4) -= 1;
			if (*(unsigned char*) (h + 0x1d) < b) {
				cm_BeginPacketFieldDelta(h, *(int*) (h + 2));
				off = h - cm_PacketDeltaBase + 0x1d;
				cm_AppendPacketFieldValue(1, 1, off, &v);
				cm_RequestChangeAttribute();
			}
		}
		if (*(int*) (u + 0xb4) != 0 || *(int*) (u + 0xb0) != 0) {
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 0xf, 0);
			return;
		}
		msg = 0x5f6;
		p = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0x10));
		if (p == 0) {
			goto kill;
		}
		r = gm_FindBuildingOwner(p);
		if (r != 0 && (*(unsigned char*) (r + 0x1b4) & 1)) {
			msg = 0x60b;
		}
		w = gm_FindBuildingPrimarySlot(p);
		io_FormatTextBuffer(text, 0x1bba, p);
		if (w != 0) {
			he_MessageBoxQuickjump(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, -1, text, 0, msg, *(int*) (p + 1), *(int*) (w + 2), 0, 0);
		} else {
			he_MessageBoxQuickjump(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, -1, text, 0, msg, *(int*) (p + 1), -1, 0, 0);
		}
		he_FreeAction(u);
		break;
	case -2:
	case -1:
	kill:
		he_FreeAction(u);
		break;
	}
}
