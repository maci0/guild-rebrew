#include <string.h>

#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_actions.h"

extern int gm_GameTime;
extern unsigned char gm_ActiveTownIndex;
extern int cm_PacketDeltaBase;
extern float g_665ee8;

extern char* __cdecl gm_ResolveParentEntity(void* record);
extern int __cdecl gm_RandomMod(int range);
extern void __cdecl gm_AddTime(void* clock, int arg2, int arg3, int arg4);
extern float __cdecl eval_ObjektPreis2Credits(int id, int pct);
extern void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);
extern void __cdecl cm_SendCopyEntityData(int block);
extern void* __cdecl gm_GetChainNodeAtIndex(int a, int b);
extern void* __cdecl gm_SearchTable67(int value);
extern int __cdecl rt_CountRoutePoints(int a);
extern void __cdecl cm_BeginPacketFieldDelta(void* record, unsigned int value);
extern void __cdecl cm_AppendCommandSyncField(int a, int b, int offset, void* value);
extern unsigned int __cdecl cm_SendSetAttribute(void);
extern void* __cdecl gm_EntityAccumulate(void* record);
extern int __cdecl ch_IsEntityNearBuildingDoor(void* record, void* entry);
extern int __cdecl gm_IsWarehouse(void* entry);

#pragma pack(push, 1)
typedef struct {
	unsigned char p00[4];
	unsigned char f04;
	unsigned char p05[3];
	int f08;
	int f0c;
	unsigned char p10[0x18];
	pos14_7f4c00 timestamp;
	unsigned char e36;
	unsigned char p37[0x21];
	int f58;
	int f5c;
	int f60;
	int f64;
	unsigned char p68[0x1c];
	int f84;
	unsigned char p88[0x16];
	unsigned char f9e;
	unsigned char p_9f[0x59];
} TIME_JOB;
#pragma pack(pop)

/* ADDRESS: GOLDTL 0x005705a0 */
/* ADDRESS: GOLDDE 0x00556560 */
void __cdecl he_ProcessTradeCartRoute(int action, char* rec)
{
	TIME_JOB job;
	char* entity;
	char* entry;
	char* found;
	int steps[5];
	int age;
	int next;
	int threshold;
	int value;
	unsigned char previous;
	float price;

	if (*(int*) (rec + 0x24) != 0)
		return;
	entity = gm_ResolveParentEntity(rec);
	threshold = (gm_RandomMod(0x20) & 0xffff) + 0x28;
	age = (unsigned char) rec[0x12];
	if (age < threshold) {
		unsigned int eid;
		memset(&job, 0, sizeof(job));
		eid = *(unsigned int*) (entity + 4);
		job.f08 = eid;
		job.f0c = eid;
		job.timestamp.a = gm_GameTime;
		job.timestamp.b = gm_GameTimeHour;
		job.f04 = 0x10;
		job.e36 = 1;
		job.timestamp.c = gm_GameTimeSliceDword;
		job.timestamp.d = gm_GameTimeTailWord;
		gm_AddTime(&job.timestamp, 0, 0, 10);
		job.f58 = *(unsigned int*) (rec + 2);
		job.f64 = 5;
		job.f84 = 0;
		job.f5c = 100 - (unsigned char) rec[0x12];
		price = eval_ObjektPreis2Credits(*(unsigned short*) rec, 100) * g_665ee8;
		value = (int) (price * (float) (100 - (unsigned char) rec[0x12]));
		cm_RequestMoveCredits(-1, *(unsigned int*) (entity + 4), (char) gm_ActiveTownIndex, value);
		cm_SendCopyEntityData((int) &job);
		return;
	}
	entry = (char*) gm_GetChainNodeAtIndex(*(unsigned int*) (rec + 0x29),
		*(unsigned int*) (rec + 0x2d));
	if (entry != 0)
		entry = (char*) gm_SearchTable67(*(unsigned int*) (entry + 4));
	if (entry != 0) {
		if (*(int*) (rec + 0x2d) == 0) {
			previous = (unsigned char) rec[0x32];
			steps[0] = 0x0c;
			steps[1] = 8;
			steps[2] = 4;
			steps[3] = 2;
			steps[4] = 0;
			next = steps[(unsigned char) rec[0x31]];
			rec[0x32] = (char) (previous + 1);
			if ((int) (unsigned char) (previous + 1) < next)
				return;
			rec[0x32] = 0;
		}
		if (ch_IsEntityNearBuildingDoor(rec, entry) != 0
			&& (gm_IsWarehouse(entry) == 0
				|| *(int*) (rec + 6) == *(int*) ((char*) *(void**) 0x7749f0 + 1))) {
			int next_idx;
			next = rt_CountRoutePoints(*(unsigned int*) (rec + 0x29));
			next_idx = *(int*) (rec + 0x2d) + 1;
			if (next_idx >= next)
				next_idx = 0;
			cm_BeginPacketFieldDelta(rec, *(unsigned int*) (rec + 2));
			cm_AppendCommandSyncField(4, 1, (int) (rec + 0x2d) - cm_PacketDeltaBase, &next_idx);
			*(unsigned int*) (action + 0x84) = cm_SendSetAttribute();
			return;
		}
		found = (char*) gm_EntityAccumulate(rec);
		if (found != 0) {
			memset(&job, 0, sizeof(job));
			job.f9e = 1;
			job.f08 = *(unsigned int*) (entity + 4);
			job.f04 = 0x0f;
			job.f0c = -1;
			job.timestamp.a = gm_GameTime;
			job.timestamp.b = gm_GameTimeHour;
			job.timestamp.c = gm_GameTimeSliceDword;
			job.timestamp.d = gm_GameTimeTailWord;
			job.e36 = 2;
			job.f58 = *(unsigned int*) (rec + 2);
			job.f5c = *(unsigned int*) (found + 1);
			job.f60 = *(unsigned int*) (entry + 1);
			cm_SendCopyEntityData((int) &job);
		}
	}
}

extern char gm_InWorldHud;
extern void* g_7749f0;
extern int __cdecl cm_GetCommandStatus(int);
extern void __cdecl he_FreeAction(char*);
extern void* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl gm_QueryEntities(int, int, int, int, int);

/* Timed action 0xA6 (route supervisor) FINISH: once the linked record is gone or the
 * phase is 0, walks every matching cart and hands it to he_ProcessTradeCartRoute, then reschedules. */
/* ADDRESS: GOLDTL 0x00570870 */
void __cdecl he_RunRouteSupervisor(char* h)
{
	char* e;
	int phase;

	if (!gm_InWorldHud)
		return;
	if (*(int*) (h + 0x84) != -1 && !cm_GetCommandStatus(*(int*) (h + 0x84)))
		return;
	phase = *(int*) (h + 0x70);
	*(int*) (h + 0x84) = -1;
	if (phase >= -2) {
		if (phase >= 0) {
			if (phase == 0) {
				g_7749f0 = gm_StartFilteredEntitySearch(1, 0, 0x44);
				e = gm_QueryEntities(0, 2, 7, 4, 0x1d);
				if (e) {
					do {
						if (*(int*) (e + 0x29) && !(e[0x20] & 1) && !(e[0x13] & 0x20) && e[0x33])
							he_ProcessTradeCartRoute((int) h, e);
						e = (char*) gm_NextEntityQueryMatch();
					} while (e);
				}
				*(pos14_7f4c00*) (h + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
				gm_AddTime(h + 0x52, 0, 0xf, 0);
			}
		} else {
			he_FreeAction(h);
		}
	}
}
