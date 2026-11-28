#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"


#pragma pack(1)
// SIZE 0x41
struct rec {
	char pad0[0x36];
	unsigned short level;
	char pad38[9];
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x174];
	char* who;
	char pad180[0x9c];
};

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* lpObjektePROT;
extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_CompareGameTime(pos14_7f4c00*, pos14_7f4c00*);

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunSuchen(char* e)
{
	char* r;
	char buf[0x200];
	OBJECT_PROTOTYPE* p;
	int amt;
	int i;

	switch (*(int*) (e + 0x70)) {
	case 0:
		*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
		return;
	case 1:
		if (*(int*) (e + 0x14) == 0 && *(int*) (e + 0x18) == 0) {
			break;
		}
		if (gm_CompareGameTime((pos14_7f4c00*) (e + 0x52), &gm_GameTime) >= 0) {
			return;
		}
		gm_ResolveEntityById((void**) (&r), 0, 0, *(int*) (e + 0xb0));
		if (r == 0) {
			*(int*) (e + 0x70) = -1;
			return;
		}
		p = &((OBJECT_PROTOTYPE*)lpObjektePROT)[*(unsigned short*) (e + 0xac)];
		amt = (gm_RandomMod((unsigned short) (p->value_036 * 40)) + p->value_036 * 40)
		    * (*(int*) (e + 0x18) + *(int*) (e + 0x14));
		cm_SendSellObjekt(*(int*) (e + 0xb4), -1, *(unsigned short*) (e + 0xac), amt, gm_ActiveTownIndex, 0);
		io_FormatTextBuffer(buf, 0x1bb8, *(unsigned short*) (e + 0xac) * 2 + 0x9a8, r, amt);
		he_MessageBoxQuickjump((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (r + 0x27)].entity_id), -1, buf, 0, 0x5f1, *(int*) (r + 1), -1, 0,
		    "_NACHRICHTEN_HS_08");
		for (i = 0; i < 768; i++) {
			if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_17c) == e) {
				he_AssignActionSlot(r, 0, (*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index), 0);
			}
		}
		he_FreeAction(e);
		return;
	case -2:
	case -1:
		for (i = 0; i < 768; i++) {
			if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_17c) == e) {
				he_AssignActionSlot(0, 0, (*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index), 0);
			}
		}
		break;
	default:
		return;
	}
	he_FreeAction(e);
}
