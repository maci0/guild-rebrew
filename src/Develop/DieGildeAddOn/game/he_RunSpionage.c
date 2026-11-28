/* Spionage job.  Picks a spy target in the watched house's neighbourhood,
   books the operation and walks it through the spy states until the report
   is delivered.  State 1 scans the residential descriptors for a matching
   house type, state 2 waits for the target, state 3 hands the record over. */
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/client_types.h"

extern char gm_EntitySlotTable[];
#include "game_data.h"
typedef struct SpyProto { unsigned char kind; unsigned char rest[0x24c]; } SpyProto;
extern unsigned char gm_ActiveTownIndex;
extern pos14_7f4c00 gm_GameTime;
extern char s_6a6578[];
extern char s_67ed14[];

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_GetScaledWorkforceOutput(unsigned char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl gm_GetSeasonTreasury(char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
void __cdecl he_FreeAction(void*);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
int __cdecl cm_SendSetHE(int, void*);
void __cdecl cm_RequestKillSpieler(int, int);
void __cdecl cm_SendCancelCharacterActions(unsigned int);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl gm_ResolveEntityById(void**, int, int, int);
int __cdecl gm_CompareGameTime(void*, void*);
int __cdecl gm_IsEntityAtBuilding(void*, void*);
char* __cdecl gm_GetEntityTableEntry(char*);

/* ADDRESS: GOLDTL 0x005624a0 */
void __cdecl he_RunSpionage(char* ctx)
{
	char text[0x400];
	unsigned char* rec;
	unsigned char* ent;
	unsigned char* hit;
	char* house;

	hit = 0;
	if (*(int*) (ctx + 0x70) == -1 || *(int*) (ctx + 0x70) == -2) {
		if ((*(unsigned char*) (ctx + 0x78) & 2)
		    && *(int*) (ctx + 0xd8) != -1) {
			ent = gm_LookupEntityRecordById(*(int*) (ctx + 0xd8));
			if (ent != 0) {
				cm_SendCancelCharacterActions(*(int*) (ent + 4));
				cm_RequestKillSpieler(*(int*) (ent + 4), 1);
			}
		}
		he_FreeAction(ctx);
		return;
	}
	if (*(unsigned char*) (ctx + 0x78) & 4) {
		return;
	}
	if (*(int*) (ctx + 0x84) != -1 && !cm_GetCommandStatus(*(int*) (ctx + 0x84))) {
		return;
	}
	switch (*(int*) (ctx + 0x70)) {
	case 0:
		if (*(int*) (ctx + 0xd8) != -1 && !cm_GetCommandStatus(*(int*) (ctx + 0xd8))) {
			return;
		}
		ent = cm_GetCommandResult(*(int*) (ctx + 0xd8));
		if (ent != 0) {
			house = gm_GetEntityTableEntry(gm_EntitySlotTable
			    + *(unsigned short*) (ctx + 8) * 0x21c);
			if (house != 0) {
				*(int*) (house + 0x28) += *(int*) (ctx + 0xe4);
			}
			*(int*) (ctx + 0xd8) = *(int*) (ent + 4);
			cm_RequestTransferCurrencyNoKill(-1, *(int*) (gm_EntitySlotTable
			    + *(unsigned short*) (ctx + 8) * 0x21c + 4), gm_ActiveTownIndex, *(int*) (ctx + 0xe4));
			he_AssignActionSlot(0, 0, *(unsigned short*) ent, ctx);
			*(pos14_7f4c00*)(ctx + 0x52) = gm_GameTime;
			*(int*) (ctx + 0x84) = cm_SendSetHE(1, ctx);
			return;
		}
		*(int*) (ctx + 0xd8) = -1;
		*(pos14_7f4c00*)(ctx + 0x52) = *(pos14_7f4c00*)(ctx + 0xc8);
		*(int*) (ctx + 0x84) = cm_SendSetHE(4, ctx);
		return;
	case 1:
	{
		int mask;
		int mask2;
		int tries;
		int idx;
		unsigned char* proto;

		idx = *(int*) (ctx + 0xbc);
		tries = 0x100;
		do {
			hit = (unsigned char*) (lpGebaeudeINST + idx * 0xa9);
			proto = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*hit];
			mask = 0;
			mask2 = 0;
			if ((((BUILDING_PROTOTYPE*)proto)->category) > 0x1f) {
				mask2 = 1 << ((((BUILDING_PROTOTYPE*)proto)->category) - 0x20);
			} else {
				mask = 1 << (((BUILDING_PROTOTYPE*)proto)->category);
			}
			if (((mask & 0xa7fcc3a6) || (mask2 & 1))
			    && *(int*) (hit + 1) != *(int*) (ctx + 0xac)) {
				break;
			}
			hit = 0;
			tries--;
			idx = (idx + *(int*) (ctx + 0xc0)) % 256;
		} while (tries != 0);
		idx = (*(int*) (ctx + 0xc0) + idx) % 256;
		*(int*) (ctx + 0xbc) = idx;
		if (hit == 0) {
			gm_AddTime(ctx + 0x52, 0, 1, 0);
			*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
			return;
		}
		io_FormatTextBuffer(text, 0x6a6578, hit);
		ent = gm_LookupEntityRecordById(*(int*) (ctx + 0xd8));
		if (ent != 0) {
			cm_SendCancelCharacterActions(*(int*) (ent + 4));
			ch_StartMovement(*(int*) (ent + 4), *(int*) (hit + 1), -1, 0, 1, s_67ed14);
			gm_AddTime(ctx + 0x52, 0, 5, 0);
			*(int*) (ctx + 0xb4) = *(int*) (hit + 1);
			*(int*) (ctx + 0x84) = cm_SendSetHE(2, ctx);
			return;
		}
		gm_AddTime(ctx + 0x52, 0, 1, 0);
		*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
		return;
	}
	case 2:
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xb4));
		gm_AddTime(ctx + 0x52, 0, 5, 0);
		if (hit == 0) {
			*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
			return;
		}
		ent = gm_LookupEntityRecordById(*(int*) (ctx + 0xd8));
		if (ent == 0) {
			gm_AddTime(ctx + 0x52, 0, 1, 0);
			*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
			return;
		}
		if (gm_IsEntityAtBuilding(ent, hit) == 0) {
			*(int*) (ctx + 0x70) = 2;
			gm_AddTime(ctx + 0x52, 0, 5, 0);
			*(int*) (ctx + 0x84) = cm_SendSetHE(2, ctx);
			return;
		}
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xac));
		if (hit != 0 && *(unsigned short*) (hit + 0x27) != 0xffff) {
			if (gm_CompareGameTime(ctx + 0xc8, &gm_GameTime) == -1) {
				cm_SendCancelCharacterActions(*(int*) (ent + 4));
				ch_StartMovement(*(int*) (ent + 4), *(int*) (hit + 1),
				    -1, 0, 1, s_67ed14);
				*(int*) (ctx + 0x84) = cm_SendSetHE(3, ctx);
				return;
			}
			*(int*) (ctx + 0x84) = cm_SendSetHE(1, ctx);
			return;
		}
		*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
		return;
	case 3:
		gm_AddTime(ctx + 0x52, 0, 5, 0);
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xac));
		if (hit != 0 && *(unsigned short*) (hit + 0x27) != 0xffff) {
			ent = gm_LookupEntityRecordById(*(int*) (ctx + 0xd8));
			if (ent != 0 && gm_IsEntityAtBuilding(ent, hit) == 0) {
				*(int*) (ctx + 0x70) = 3;
				gm_AddTime(ctx + 0x52, 0, 5, 0);
				*(int*) (ctx + 0x84) = cm_SendSetHE(3, ctx);
				return;
			}
			rec = gm_LookupEntityRecordById(*(int*) (ctx + 0xc4));
			if (rec != 0) {
				io_FormatTextBuffer(text, 0x1734, *(unsigned short*) rec);
				he_PostEntityMessage(*(int*) (gm_EntitySlotTable
				    + *(unsigned short*) (ctx + 8) * 0x21c + 4),
				    -1, text, 0, 0x5fa, 0);
			}
		}
		*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
		return;
	case 4:
		gm_AddTime(ctx + 0x52, 0, 1, 0);
		*(int*) (ctx + 0x84) = cm_SendSetHE(-1, ctx);
		return;
	default:
		return;
	}
}
