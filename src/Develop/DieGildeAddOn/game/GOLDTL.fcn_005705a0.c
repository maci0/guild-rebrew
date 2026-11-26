#include <string.h>

#include "client_types.h"
#include "client_actions.h"

extern int gm_GameTime;
extern unsigned char g_773d75;
extern int g_aed32c;
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
void __cdecl fcn_005705a0(int action, char* rec)
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
		job.timestamp.b = g_7f4c04;
		job.f04 = 0x10;
		job.e36 = 1;
		job.timestamp.c = g_7f4c08;
		job.timestamp.d = g_7f4c0c;
		gm_AddTime(&job.timestamp, 0, 0, 10);
		job.f58 = *(unsigned int*) (rec + 2);
		job.f64 = 5;
		job.f84 = 0;
		job.f5c = 100 - (unsigned char) rec[0x12];
		price = eval_ObjektPreis2Credits(*(unsigned short*) rec, 100) * g_665ee8;
		value = (int) (price * (float) (100 - (unsigned char) rec[0x12]));
		cm_RequestMoveCredits(-1, *(unsigned int*) (entity + 4), (char) g_773d75, value);
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
			cm_AppendCommandSyncField(4, 1, (int) (rec + 0x2d) - g_aed32c, &next_idx);
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
			job.timestamp.b = g_7f4c04;
			job.timestamp.c = g_7f4c08;
			job.timestamp.d = g_7f4c0c;
			job.e36 = 2;
			job.f58 = *(unsigned int*) (rec + 2);
			job.f5c = *(unsigned int*) (found + 1);
			job.f60 = *(unsigned int*) (entry + 1);
			cm_SendCopyEntityData((int) &job);
		}
	}
}
