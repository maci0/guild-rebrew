extern char gm_LawEntries[];
extern char gm_LawEntries[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

/* ADDRESS: GOLDTL 0x004f4830 */
/* ADDRESS: GOLDDE 0x004e08f0 */
int __cdecl gm_GetLawEntry(int idx, void* dst)
{
	if (idx >= 0x1d) {
		return 0;
	}
	memcpy(dst, (void*) (gm_LawEntries + idx * 36), 36);
	return 1;
}

#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl gm_FormatLawName(char* buf, int k);
void __cdecl he_NotifyLawChange(char* o, char* buf);

/* ADDRESS: GOLD 0x004f27d0 */
/* ADDRESS: GOLDTL 0x004f48e0 */
/* ADDRESS: GOLDDE 0x004e09a0 */
int __cdecl gm_ApplyLawChange(char* msg)
{
	int rec[9];
	char buf[0x100];
	char* entity;

	if (gm_GetLawEntry(*(unsigned char*) (msg + 4), rec) == 0) {
		return 0;
	}
	*(int*) (gm_LawEntries + *(unsigned char*) (msg + 4) * 36 + 0x18) = *(int*) (msg + 5);
	if (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id != *(int*) msg) {
		entity = gm_LookupEntityRecordById(*(int*) msg);
		if (entity != 0) {
			gm_FormatLawName(buf, *(unsigned char*) (msg + 4));
			he_NotifyLawChange(entity, buf);
		}
	}
	return 1;
}

extern char g_9a3825[];


/* ADDRESS: GOLD 0x004f39e0 */
/* ADDRESS: GOLDTL 0x004f5dd0 */
/* ADDRESS: GOLDDE 0x004e1bb0 */
int __cdecl gm_SumStraftatSeverity(int entityId)
{
	int buf[9];
	int sum;
	int cursor;

	sum = 0;
	for (cursor = (int) g_9a3825; cursor < (int) (g_9a3825 + 0x5a00); cursor += 0x2d) {
		if (*(int*) (cursor - 0xf) == entityId && *(int*) cursor == 1) {
			gm_GetLawEntry(*(unsigned char*) (cursor - 9), buf);
			sum += buf[3];
		}
	}
	return sum;
}
