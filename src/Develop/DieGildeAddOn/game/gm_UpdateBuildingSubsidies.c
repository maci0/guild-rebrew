extern char g_85a210[];
extern char gm_EntitySlotTable[];
#include <stdlib.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int gm_QueuedCommandCount;
extern unsigned char gm_ActiveTownIndex;
extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
char* __cdecl gm_FindPublicTreasury(int a);
int __cdecl gm_GetLawEntry(int idx, void* dst);
int __cdecl gm_ConvertUnitsToAmount(int a, unsigned char b);
void __cdecl cm_StepCommandQueue(void);
int __cdecl gm_AccumulateTyped2(char* rec);
void __cdecl cm_RequestCopyEntityData(int a1, int a2, int a3, int a4);
float __cdecl gm_ApplyEntityHealthDelta(int a, int b);
void __cdecl cm_RequestTransferCurrencyNoKill(int a1, int a2, char a3, int a4);

/* ADDRESS: GOLDTL 0x004fcc20 */
/* ADDRESS: GOLDDE 0x004e8750 */
void __cdecl gm_UpdateBuildingSubsidies(void)
{
	int handle;
	char buf[0x24];
	int i;
	int n;
	int r;
	char* rec;
	char* q;
	char* e;

	handle = (int) gm_FindPublicTreasury(1);
	gm_GetLawEntry(5, buf);
	r = 0xe - *(int*) (buf + 0x18); n = gm_ConvertUnitsToAmount(r, gm_ActiveTownIndex);
	i = 0;
	gm_QueuedCommandCount = 0;
	q = (char*) ((int) &gm_EntitySlotTable + 0x170);
	do {
		rec = q - 0x170;
		if (gm_QueuedCommandCount > 0x40) {
			cm_StepCommandQueue();
			gm_QueuedCommandCount = 0;
		}
		if (*(unsigned short*) rec != 0xffff && *(unsigned char*) (rec + 8) != 0 && *(unsigned char*) (rec + 2) == 0 && *(int*) (rec + 0x170) != 0) {
			e = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) *(int*) (rec + 0x170)];
			r = gm_AccumulateTyped2(rec);
			if (r < 0) {
				int obj;

				obj = *(int*) (rec + 0x16c);
				if (*(int*) (rec + 0x16c) == 0 && *(int*) (rec + 0x5c) == -1) {
					r = abs(r);
					if (r > n * 2) {
						gm_ApplyEntityHealthDelta(i, 0xffffec78);
						goto inc;
					}
				}
				if (obj != 0) {
					cm_RequestCopyEntityData(((ENTITY_RECORD*) &gm_EntitySlotTable)[*(unsigned short*) (obj + 0x27)].entity_id,
					    *(int*) (rec + 4), -0xa, 1);
					gm_QueuedCommandCount++;
				}
			}
			if (*e == 1) {
				cm_RequestTransferCurrencyNoKill(*(int*) (handle + 2), *(int*) (rec + 4), 0, n);
			inc:
				gm_QueuedCommandCount++;
			}
		}
		q += sizeof(ENTITY_RECORD);
		i++;
	} while ((int) q < (int) &g_85a210);
	gm_QueuedCommandCount = 0;
}
