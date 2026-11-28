#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include <string.h>

typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

extern char* g_14a9aa8;
extern char* g_14a9ab4;
extern char* g_14a9ac0;
extern char str_empty[];

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_FindRecordById(int);
int __cdecl gm_CalcEntityInventoryStats(char* e, Stats* s);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl cut_GetBuildingCombatType(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_SendCmdMessage(char*, char*, char*, char*);

// Sends the two parties of a transfer (+0x34, +0x38) their message pair,
// chosen by the flag byte at +0x7c (1, 2 or 4). With flag 1 set, every
// listed record (+0x100, -1 = none) must exist and hold a positive total.

/* ADDRESS: GOLDTL 0x004d74b0 */
/* ADDRESS: GOLDDE 0x004c4400 */
int __cdecl cut_NotifyCombatCutscene(char* event)
{
	int i;
	int combatType;
	char* partyB;
	int targetObj;
	char buf[0x400];
	Stats st;
	char* partyA;
	char* entry;
	int* targetIds;
	unsigned char flags;

	partyA = gm_LookupEntityRecordById(*(int*) (event + 0x34));
	partyB = gm_LookupEntityRecordById(*(int*) (event + 0x38));
	if (partyA == 0 || partyB == 0 || partyA == partyB) {
		return 0;
	}
	if (event[0x7c] & 1) {
		targetIds = (int*) (event + 0x100);
		for (i = 0; i < 3; i++) {
			if (targetIds[i] != -1) {
				entry = gm_FindRecordById(targetIds[i]);
				if (entry == 0) {
					return 0;
				}
				gm_CalcEntityInventoryStats(entry, &st);
				if (st.xb0 <= 0) {
					return 0;
				}
			}
		}
	}
	targetObj = gm_SearchTable67(*(int*) (event + 0x14));
	if (!gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0x10c))) {
		return 0;
	}
	flags = event[0x7c];
	if (flags & 1) {
		io_FormatTextBuffer(buf, 0x11e0, *(unsigned short*) partyB);
		strcat(buf, g_14a9aa8);
		he_SendCmdMessage(partyA, event, buf, str_empty);
		io_FormatTextBuffer(buf, 0x11e1, *(unsigned short*) partyA);
		strcat(buf, g_14a9aa8);
		he_SendCmdMessage(partyB, event, buf, str_empty);
	} else if (flags & 2) {
		combatType = cut_GetBuildingCombatType(gm_SearchTable67(*(int*) (event + 0x10c))) + 0x1125;
		io_FormatTextBuffer(buf, 0x11e3, combatType, *(unsigned short*) partyB, targetObj);
		strcat(buf, g_14a9ab4);
		he_SendCmdMessage(partyA, event, buf, str_empty);
		io_FormatTextBuffer(buf, 0x11e4, *(unsigned short*) partyA, combatType, targetObj);
		strcat(buf, g_14a9ab4);
		he_SendCmdMessage(partyB, event, buf, str_empty);
		return 1;
	} else if (flags & 4) {
		io_FormatTextBuffer(buf, 0x11e6, *(unsigned short*) partyB);
		strcat(buf, g_14a9ac0);
		he_SendCmdMessage(partyA, event, buf, str_empty);
		io_FormatTextBuffer(buf, 0x11e7, *(unsigned short*) partyA);
		strcat(buf, g_14a9ac0);
		he_SendCmdMessage(partyB, event, buf, str_empty);
	}
	return 1;
}
