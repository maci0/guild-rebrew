#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#pragma pack(push, 1)

/* SIZE 0x29 */
typedef struct {
	unsigned char office;
	int id;
	char pad5[0x22];
	unsigned short slot;
} Player;

/* SIZE 0x21c */
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x15c];
	unsigned char kind;
	char pad165[0xb7];
} Entity;

/* SIZE 0x24d */
typedef struct {
	unsigned char kind;
	char pad1[0x222];
	unsigned char slots[6];
	char pad229[6];
	unsigned char f22f;
	unsigned char f230;
	char pad231[0x1c];
} Office;

/* SIZE 0xf8 */
typedef struct {
	int f0;
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	int f10;
	int f14;
	char pad18[0x10];
	pos14_7f4c00 pos;
	unsigned char b36;
	char pad37[0x21];
	int f58;
	int f5c;
	char pad60[0x98];
} Msg;

#pragma pack(pop)

extern unsigned char *lpGebaeudePROT;
extern unsigned char *lpGebaeudeINST;
extern unsigned char *gm_CityEntity;
extern char g_7f4ca0[];
extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;
extern int g_6a3424;
extern unsigned char g_6a3440;

int __cdecl gm_RandomMod(int);
void __cdecl d3_TransformPoint(char *, char *, char *);
void __cdecl cm_FlushCommandQueue(void);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_GetCommandResult(int);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_BeginPacketFieldDelta(char *, int);
int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char *);
void __cdecl cm_PollCommandQueue(void);
void __cdecl cm_ExecCommand(void);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_SendSellObjekt(int, int, short, int, char, int);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cm_SendCopyEntityData(Msg *);
int __cdecl cm_SendSetGebBesitzer(int, int, int);
void __cdecl cm_RequestSetWohnsitz(int, int);
int __cdecl cm_RequestAssignWorker(unsigned char *, int, int, int);
int __cdecl cm_RequestCreateGeb(int, int, char *, float *);
void __cdecl gm_UpdateEconomyStats(void);
int __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl gm_FindNearestEligibleEntity(unsigned char *, int);
int __cdecl gm_CheckEntityType(unsigned char *);
int __cdecl gm_JobToBuildingType(int);
int __cdecl gm_ConvertUnitsToAmount(int, char);
int __cdecl gm_CalculateGebaeudeValue(unsigned char *, int);
int __cdecl gm_GetTypeProductValue(int);
void __cdecl amt_InitOfficeHolders(int);
void __cdecl init_Betrieb(unsigned char *);
void __cdecl init_SetupBetriebWorkers(unsigned char *);
void __cdecl cm_StepCommandQueue(void);
void __cdecl d2_SetProgressPercent(int, int);
void __cdecl he_EnsureAction0x6d(void);
void __cdecl he_EnsureAction0x6b(void);
void __cdecl he_EnsureAction0x7a(void);
void __cdecl he_EnsureCityBuilding0x2bActions(void);
int __cdecl lc_GetBauplatzPrefix(int, char *);
int __cdecl d3_CollectUnusedSceneObjects(char *, char **);
void __cdecl d3_ComputeObjectYawToTarget(float *, int);

/* ADDRESS: GOLDTL 0x00512ee0 */
void __cdecl gm_InitStartingEntitiesAndRelations(void)
{
	int i = 0;
	int total = 0;
	char kinds[34] = {0, 0, 3, 0, 1, 1, 0, 1, 1, 1, 0, 2, 2, 2, 1, 0,
			2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 3, 1, 0, 1, 1, 0};
	char *e;
	char *f;
	Player *p;
	BUILDING_PROTOTYPE *o;
	int j;
	int k;
	int h;
	int q;
	int res;
	int done;
	int outer;
	int inner;
	int count;
	unsigned int kind;
	unsigned short slot;
	{
	int counts[34];
	int found[8];
	int handles[16];
	char path[16];
	char name[96];
	int list[128];
	float pos3[3];

	memset(counts, 0, sizeof(counts));
	memset(found, 0, sizeof(found));
	memset(handles, 0, sizeof(handles));
	for (e = g_7f4ca0 + 2; (int)e < 0x85a0a2; e += sizeof(ENTITY_RECORD)) {
		if (total >= 8)
			break;
		if (*(unsigned short *)(e - 2) != 0xffff
				&& (*e == 6 || *e == 7 || *e == 5)) {
			found[total] = (int)(e - 2);
			total++;
		}
	}
	for (i = 0; i < total; i++) {
		e = (char *)found[i];
		if (e == 0)
			continue;
		if (!(*(unsigned char *)(e + 2) == 6 || *(unsigned char *)(e + 2) == 7
				|| *(unsigned char *)(e + 2) == 5))
			continue;
		done = 0;
		inner = 0;
		do {
			p = (Player *)(lpGebaeudeINST + inner);
			if (p->office != 0 && p->slot == 0xffff) {
				o = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p->office];
				for (j = 0; j < 6; j++) {
					if (o->worker_kind[j] != 0
							&& o->worker_kind[j] == *(unsigned char *)(e + 0x164)) {
						h = cm_SendSetGebBesitzer(p->id, *(int *)(e + 4),
								*(int *)(e + 4));
						while (cm_GetCommandStatus(h) == 0) {
							cm_StepCommandQueue();
						}
						init_SetupBetriebWorkers((unsigned char *)p);
						done = 1;
						counts[o->category]++;
						break;
					}
				}
			}
			if (done)
				break;
			inner += 0xa9;
		} while (inner < 0xa900);
		if (!done) {
			kind = gm_JobToBuildingType(*(unsigned char *)(e + 0x164));
			if (lc_GetBauplatzPrefix(kind, name)
					&& (res = d3_CollectUnusedSceneObjects(name, (char **)list)) != 0) {
				j = 0;
				if (res >= 1) {
					do {
						if (list[j])
							break;
						j++;
					} while (j < res);
				}
				d3_TransformPoint((char *)list[j], (char *)(list[j] + 0x4c), path);
				d3_ComputeObjectYawToTarget(pos3, list[j]);
				h = cm_RequestCreateGeb(*(int *)(e + 4), kind, path, pos3);
				if (h != -1) {
					while (cm_GetCommandStatus(h) == 0) {
						cm_StepCommandQueue();
					}
				}
				h = cm_GetCommandResult(h);
				if (h)
					init_SetupBetriebWorkers((unsigned char *)h);
			}
		}
	}

	d2_SetProgressPercent(0, 0x55);
	for (i = 0; i < total; i++) {
		e = (char *)found[i];
		if (e == 0)
			continue;
		h = gm_StartFilteredEntitySearch(1, 4, *(unsigned short *)e);
		if (h && gm_CheckEntityType((unsigned char *)h))
			h = 0;
		if (*(unsigned char *)(e + 2) != 5 && *(unsigned char *)(e + 2) != 4) {
			if (h) {
				q = gm_FindNearestEligibleEntity((unsigned char *)h, 4);
				if (!q) {
					q = gm_FindNearestEligibleEntity((unsigned char *)h, 5);
					if (!q)
						break;
				}
			} else {
				q = gm_StartFilteredEntitySearch(2, 0, 4, 4, 0xffff);
				if (!q) {
					q = gm_StartFilteredEntitySearch(2, 0, 5, 4, 0xffff);
					if (!q)
						break;
				}
			}
		} else if (h) {
			q = gm_FindNearestEligibleEntity((unsigned char *)h, 5);
			if (!q) {
				q = gm_FindNearestEligibleEntity((unsigned char *)h, 4);
				if (!q)
					break;
			}
		} else {
			q = gm_StartFilteredEntitySearch(2, 0, 5, 4, 0xffff);
			if (!q) {
				q = gm_StartFilteredEntitySearch(2, 0, 4, 4, 0xffff);
				if (!q)
					break;
			}
		}
		cm_RequestSetWohnsitz(*(int *)(e + 4), *(int *)(q + 1));
		h = cm_SendSetGebBesitzer(*(int *)(q + 1), *(int *)(e + 4), *(int *)(e + 4));
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
	}

	d2_SetProgressPercent(0, 0x5a);
	for (k = 0xb; k <= 0xd; k++) {
		e = (char *)gm_StartFilteredEntitySearch(2, 4, 0xffff, 5, k);
		if (e == 0)
			continue;
		count = gm_CalculateGebaeudeValue((unsigned char *)e, 100);
		cm_BeginPacketFieldDelta(e, *(int *)(e + 1));
		cm_AppendPacketFieldDelta(4, 1, 0x65, (char *)&count);
		count = count * 2;
		cm_AppendPacketFieldDelta(4, 1, 0x69, (char *)&count);
		cm_RequestChangeAttribute();
		o = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char *)e];
		cm_SendSetGebBesitzer(*(int *)(e + 1), *(int *)(gm_CityEntity + 4),
				*(int *)(gm_CityEntity + 4));
		cm_RequestAssignWorker((unsigned char *)e, 1, o->role_230, o->worker_kind[0]);
		cm_RequestAssignWorker((unsigned char *)e, 0, o->role_22f, 0);
		cm_RequestAssignWorker((unsigned char *)e, 0, o->role_22f, 0);
		cm_SendSellObjekt(*(int *)(e + 1), -1, 0x135, 1, g_773d75, 0);
		counts[k]++;
	}

	d2_SetProgressPercent(0, 0x5f);
	e = (char *)gm_StartFilteredEntitySearch(2, 4, 0xffff, 5, 0x10);
	if (e) {
		o = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char *)e];
		h = cm_RequestAssignWorker((unsigned char *)e, 2, o->role_230, 0x2d);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
		h = *(int *)(cm_GetCommandResult(h) + 4);
		cm_SendSetGebBesitzer(*(int *)(e + 1), h, h);
		cm_RequestAssignWorker((unsigned char *)e, 0, o->role_22f, 0);
		cm_RequestAssignWorker((unsigned char *)e, 0, o->role_230, 0);
		cm_SendSellObjekt(*(int *)(e + 1), -1, 0x135, 1, g_773d75, 0);
		counts[0x10]++;
	}

	if (g_6a3424) {
		outer = 0;
		for (inner = 0; inner < 0xa900; inner += 0xa9) {
			p = (Player *)(lpGebaeudeINST + inner);
			if (p->office == 0 || p->slot != 0xffff)
				continue;
			o = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p->office];
			kind = o->category;
			if (kinds[kind] != 1 || counts[kind] >= 2)
				continue;
			slot = 0;
			cm_BeginCommandSync();
			for (j = 5; j >= 0; j--) {
				if (o->worker_kind[j]) {
					slot = o->worker_kind[j];
					break;
				}
			}
			h = cm_RequestAssignWorker((unsigned char *)p, 2, o->role_230, slot);
			while (cm_GetCommandStatus(h) == 0) {
				cm_StepCommandQueue();
			}
			q = cm_GetCommandResult(h);
			cm_SendSetGebBesitzer(p->id, *(int *)(q + 4), *(int *)(q + 4));
			count = gm_ConvertUnitsToAmount(3000, g_773d75);
			cm_RequestMoveCredits(*(int *)(q + 4), -1, g_773d75, count);
			if (outer <= 0xf) {
				handles[outer] = q;
				outer++;
			}
			kind = o->category;
			if (kind != 9 && kind != 5) {
				if (kind != 4 && kind != 0x10 && kind != 0x13) {
					cm_RequestAssignWorker((unsigned char *)p, 0, o->role_22f, 0);
				} else {
					cm_RequestAssignWorker((unsigned char *)p, 0, o->role_22f, 0);
					cm_RequestAssignWorker((unsigned char *)p, 0, o->role_230, 0);
				}
			}
			cm_SendSellObjekt(p->id, -1, 0x135, 1, g_773d75, 0);
			if (o->category == 5) {
				count = gm_ConvertUnitsToAmount(6000, g_773d75);
				cm_RequestMoveCredits(*(int *)(q + 4), -1, g_773d75, count);
			}
			init_Betrieb((unsigned char *)p);
			cm_EndCommandSync();
			counts[o->category]++;
		}
		while (cm_AreQueuedCommandsDone() == 0) {
			cm_FlushCommandQueue();
			cm_PollCommandQueue();
			cm_ExecCommand();
		}
		for (i = 0; i < outer; i++) {
			e = (char *)handles[i];
			if (e == 0)
				continue;
			h = gm_StartFilteredEntitySearch(1, 4, *(unsigned short *)e);
			if (h == 0 || gm_CheckEntityType((unsigned char *)h) != 0) {
				q = gm_StartFilteredEntitySearch(2, 0, 5, 4, 0xffff);
				if (!q) {
					q = gm_StartFilteredEntitySearch(2, 0, 4, 4, 0xffff);
					if (!q)
						goto release_handles;
				}
			} else {
				q = gm_FindNearestEligibleEntity((unsigned char *)h, 5);
				if (!q) {
					q = gm_FindNearestEligibleEntity((unsigned char *)h, 4);
					if (!q)
						goto release_handles;
				}
			}
			cm_RequestSetWohnsitz(*(int *)(e + 4), *(int *)(q + 1));
			h = cm_SendSetGebBesitzer(*(int *)(q + 1), *(int *)(e + 4),
					*(int *)(e + 4));
			while (cm_GetCommandStatus(h) == 0) {
				cm_StepCommandQueue();
			}
		}
		goto handles_done;
release_handles:
		for (; i < outer; i++) {
			e = (char *)handles[i];
			if (e) {
				cm_RequestMoveCredits(*(int *)(e + 4), -1, g_773d75,
						gm_GetTypeProductValue(4));
			}
		}
handles_done:
		;
	}
	}
	{
	Msg msg;

	cm_BeginCommandSync();
	for (inner = 0; inner < 0xa900; inner += 0xa9) {
		p = (Player *)(lpGebaeudeINST + inner);
		o = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[p->office];
		slot = p->slot;
		kind = o->category;
		if (slot != 0xffff) {
			if (kinds[kind] == 2 || kinds[kind] == 1) {
				e = (char*)&((ENTITY_RECORD*)g_7f4ca0)[slot];
				if (*(unsigned char *)(e + 2) == 5
						|| *(unsigned char *)(e + 2) == 4) {
					if (g_6a3424) {
						if (kind != 9 && kind != 5) {
							if (kind != 4 && kind != 0x10 && kind != 0x13) {
								cm_RequestAssignWorker((unsigned char *)p, 0, o->role_22f, 0);
							} else {
								cm_RequestAssignWorker((unsigned char *)p, 0, o->role_22f, 0);
								cm_RequestAssignWorker((unsigned char *)p, 0, o->role_230, 0);
							}
						}
						cm_RequestAssignWorker((unsigned char *)p, 1, o->role_230, o->worker_kind[0]);
						cm_SendSellObjekt(p->id, -1, 0x135, 1, g_773d75, 0);
						init_Betrieb((unsigned char *)p);
					}
					continue;
				}
			}
		}
		if (kinds[o->category] == 0 && slot == 0xffff)
			cm_SendSetGebBesitzer(p->id, *(int *)(gm_CityEntity + 4),
					*(int *)(gm_CityEntity + 4));
	}
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_FlushCommandQueue();
		cm_PollCommandQueue();
		cm_ExecCommand();
	}
	amt_InitOfficeHolders(0);
	gm_UpdateEconomyStats();
	e = (char *)gm_StartFilteredEntitySearch(1, 6);
	while (e) {
		if (*(short *)(e + 0x25) == -1 && *e != 'E' && *e != 'D' && *e != 'F') {
			msg.b4 = 0x1b;
			msg.f8 = *(int *)(gm_CityEntity + 4);
			msg.fc = -1;
			msg.b36 = 2;
			msg.f58 = *(int *)(e + 1);
			msg.f5c = gm_CalculateGebaeudeValue((unsigned char *)e, (char)e[0x5c]);
			cm_SendSetGebBesitzer(*(int *)(e + 1), *(int *)(gm_CityEntity + 4),
					*(int *)(gm_CityEntity + 4));
			cm_SendCopyEntityData(&msg);
		}
		e = (char *)gm_FindNextFilteredEntity();
	}
	if (g_6a3440 == 5) {
		k = 0;
		for (e = g_7f4ca0 + 2; (int)e < (int)(g_7f4ca0 + 0x65402); e += sizeof(ENTITY_RECORD)) {
			if (*e == 6)
				break;
			k++;
		}
		memset(&msg, 0, sizeof(msg));
		msg.b4 = 0x4c;
		msg.f8 = *(int *)((char*)&((ENTITY_RECORD*)g_7f4ca0)[k].entity_id);
		msg.fc = msg.f8;
		msg.f10 = 0;
		msg.f14 = 0;
		msg.pos = gm_GameTime;
		msg.b36 = 1;
		cm_SendCopyEntityData(&msg);
	}
	he_EnsureAction0x6d();
	he_EnsureAction0x6b();
	he_EnsureAction0x7a();
	he_EnsureCityBuilding0x2bActions();
	outer = 0;
	for (e = g_7f4ca0 + 2; e < g_7f4ca0 + 0x651e6; e += sizeof(ENTITY_RECORD)) {
		if (*e == 6 || *e == 7 || *e == 5 || *e == 3 || *e == 4 || *e == 2) {
			total = 0;
			if (outer + 1 < 0x300) {
				for (f = e + sizeof(ENTITY_RECORD); f < g_7f4ca0 + 0x65402; f += sizeof(ENTITY_RECORD)) {
					if (!(*f == 6 || *f == 7 || *f == 5 || *f == 3 || *f == 4
								|| *f == 2))
						continue;
					cm_RequestCopyEntityData(*(int *)(e + 2), *(int *)(f + 2),
							(int)(gm_RandomMod(0x40) & 0xffff) - 0x20, 0);
					res = cm_RequestCopyEntityData(*(int *)(f + 2), *(int *)(e + 2),
							(int)(gm_RandomMod(0x40) & 0xffff) - 0x20, 0);
					total += 2;
					if (res != -1 && total % 10 == 0) {
						while (cm_GetCommandStatus(res) == 0) {
							cm_StepCommandQueue();
						}
					}
				}
			}
		}
		outer++;
	}
	}
}
