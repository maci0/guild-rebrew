void __cdecl gv_MatchEntityGraveyardSlot();
void __cdecl gv_IsGraveSlotFree();
extern char g_7f4c00[];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
int __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_0047d220(char* p);
void* __cdecl fcn_004f18d0(char* a1, char* a2, int a3, int a4, int a5);
int __cdecl gv_CalcGraveUpgradePrice(int a, int b, int c, int* out);
int __cdecl gm_GetSeasonTreasury(int a, char b);
int __cdecl gv_CalcGravePrice(char* a1, int a2, int a3, int a4, int* out);
int __cdecl gm_GetEntitySlotIndex(int a, int* b);
int __cdecl fcn_0042e410(int a);
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST; extern unsigned char gm_ActiveTownIndex; extern float g_664160;
/* ADDRESS: GOLDTL 0x0048fe70 */
/* ADDRESS: GOLDDE 0x0047ed40 */
int __cdecl ai_StartHandleGrave(int unused0, char* actorEntity, int busy, int* out1, int* out2, int* out3)
{
	int cand[8];
	char* rec;
	int* graveSlot;
	int* targetSlot;
	int n;
	int i;
	int grade;
	int out;
	int treasury;
	graveSlot = 0;
	if (busy != 0) {
		return 0;
	}
	if (unused0 != 0) {
		return 0;
	}
	if (*(unsigned short*) (actorEntity + 0x50) == 0x7fff) {
		return 0;
	}
	if ((*(int*) ((int) &g_7f4c00 + 0x4) & 0xffff) % 6 != (unsigned) (*(int*) (actorEntity + 4)) % 6) {
		return 0;
	}
	if (*(int*) &g_7f4c00 % 3 != (unsigned) (*(int*) (actorEntity + 4)) % 3) {
		return 0;
	}
	if (*(char*) (actorEntity + 2) != 5) {
		rec = (char*) gm_LookupEntityRecordById(*(int*) (actorEntity + 0x5c));
		if (rec != 0) {
			if (*(char*) (rec + 2) == 5) {
				return 0;
			}
			if (*(char*) (rec + 9) == 0 && fcn_0047d220(rec) != 0) {
				return 0;
			}
		}
	}
	rec = (char*) lpGebaeudeINST;
	for (i = 0; i < 8; i++) {
		cand[i] = 0;
	}
	n = 0;
	busy = 0;
	do {
		if (*rec != 0 && (rec[0x5a] & 1) == 0
		    && ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *rec].category == 0x1d) {
			if (n < 8) {
				cand[n] = (int) rec;
				n++;
			}
			graveSlot = (int*) fcn_004f18d0(actorEntity, rec, 0, (int) gv_MatchEntityGraveyardSlot, 0xff);
			if (graveSlot != 0) {
				break;
			}
		}
		rec += 0xa9;
		busy++;
	} while (busy < 0x100);

	if (graveSlot != 0) {
		if (*graveSlot == 3) {
			return 0;
		}
		grade = 3;
		if (*graveSlot >= 3) {
			return 0;
		}
		do {
			targetSlot = (int*) fcn_004f18d0(0, rec, 0, (int) gv_IsGraveSlotFree, grade);
			if (targetSlot != 0) {
				break;
			}
			grade--;
		} while (grade > *graveSlot);
		if (targetSlot != 0) {
			out = gv_CalcGraveUpgradePrice((int) actorEntity, *graveSlot, *targetSlot, &busy);
			treasury = gm_GetSeasonTreasury((int) actorEntity, gm_ActiveTownIndex);
			if ((int) ((float) treasury * g_664160) <= out) {
				return 0;
			}
			out1[4] = 5;
			*(int*) ((char*) out1 + 0xc) = *(int*) (rec + 1);
			out1[1] = *targetSlot;
			out1[2] = out;
			out2[1] = *graveSlot;
			out2[4] = gm_GetEntitySlotIndex(*(int*) (rec + 0x65), graveSlot);
			return 0x3e;
		}
	} else if (n != 0
	    && 0x23 <= (fcn_0042e410(8) & 0xffff) + *(unsigned short*) (actorEntity + 0xa)) {
		graveSlot = (int*) cand[fcn_0042e410(n) & 0xffff];
		targetSlot = (int*) fcn_004f18d0(0, (char*) graveSlot, 0, (int) gv_IsGraveSlotFree, 0xff);
		if (targetSlot != 0) {
			int price, dummy;
			price = gv_CalcGravePrice((int) actorEntity, 0xff, *targetSlot, 1, &dummy);
			treasury = gm_GetSeasonTreasury((int) actorEntity, gm_ActiveTownIndex);
			if ((int) ((float) treasury * g_664160) < price) {
				return 0;
			}
			out1[4] = 4;
			*(int*) ((char*) out1 + 0xc) = *(int*) ((char*) graveSlot + 1);
			out1[1] = *targetSlot;
			out1[2] = price;
			return 0x3e;
		}
	}
	return 0;
}
