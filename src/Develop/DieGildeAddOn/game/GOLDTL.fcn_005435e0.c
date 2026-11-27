


#include <string.h>

// SIZE 0x8c
typedef struct {
	unsigned char spouse_look;
	unsigned char child_look;
	char enabled;
	unsigned char look;
	int face;
	unsigned char hair;
	unsigned char body;
	char name[0x20];
	char family[0x22];
	int dynasty;
	char skills[5];
	char motto[0x33];
	int emblem;
} Setup;

// SIZE 0x208
typedef struct {
	unsigned short slot;
	char pad2[2];
	int id;
	char pad8[0x28];
	char name[0x10];
	char family[0x10];
	short look;
	char pad52[2];
	int home;
	char pad58[4];
	int spouse;
	int partner;
	int child;
	int parent;
	char pad6c[0x14];
	char skills[5];
	char pad85[0x107];
	int emblem;
	char pad190[0x64];
	char motto[0x14];
} Figure;

extern char g_7e23e0[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
extern signed char g_6a3440;

#ifdef REBREW_GOLD
void __cdecl gm_ClearMissionJobs(void);
#else
void __cdecl gm_ClearMissionTable(void);
#endif
void __cdecl cm_BeginCommandSync(void);
int __cdecl cm_SendAllocClientSpieler(int, int, int, unsigned char, int, unsigned char, unsigned char, char*, char*);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_StepCommandQueue(void);
Figure* __cdecl cm_GetCommandResult(int);
int __cdecl cm_RequestAllocSpieler(int, int, int, short, int, unsigned char, int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_SelectEntityHeadSet(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
void __cdecl gm_AllocMissionJob(int, int, int);

void __cdecl gm_CreateSetupFamily(void)
{
	Figure* p;
	Figure* spouse;
	Figure* child;
	int h;
	int i;

#ifdef REBREW_GOLD
	gm_ClearMissionJobs();
#else
	gm_ClearMissionTable();
#endif
	if ((*(Setup*)g_7e23e0).enabled == 0) {
		return;
	}
	cm_BeginCommandSync();
	h = cm_SendAllocClientSpieler(-1, -1, 0x10, (*(Setup*)g_7e23e0).look, (*(Setup*)g_7e23e0).face, (*(Setup*)g_7e23e0).hair, (*(Setup*)g_7e23e0).body,
		(*(Setup*)g_7e23e0).name, (*(Setup*)g_7e23e0).family);
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_StepCommandQueue();
	}
	p = cm_GetCommandResult(h);
	cm_BeginCommandSync();
	h = cm_RequestAllocSpieler(9, -1, -1, gm_RandomMod(4) + 0x20, -1, (*(Setup*)g_7e23e0).child_look, 0, 1);
	i = cm_RequestAllocSpieler(9, -1, -1, gm_RandomMod(4) + 0x20, -1, (*(Setup*)g_7e23e0).spouse_look, 0, 0);
	cm_EndCommandSync();
	while (cm_AreQueuedCommandsDone() == 0) {
		cm_StepCommandQueue();
	}
	child = cm_GetCommandResult(h);
	spouse = cm_GetCommandResult(i);
	strncpy(spouse->family, (*(Setup*)g_7e23e0).family, 0x10);
	child->look = p->look;
	child->home = p->home;
	child->parent = p->id;
	strcpy(child->name, gm_FemaleNames[gm_RandomMod(0x70)]);
	gm_SelectEntityHeadSet(child->slot);
	spouse->look = p->look;
	spouse->home = p->home;
	spouse->parent = p->id;
	strcpy(spouse->name, g_14a5dbc[gm_RandomMod(0xbf)]);
	gm_SelectEntityHeadSet(spouse->slot);
	child->spouse = spouse->id;
	spouse->spouse = child->id;
	p->partner = spouse->id;
	p->child = child->id;
	child->parent = p->id;
	spouse->parent = p->id;
	strcpy(p->motto, (*(Setup*)g_7e23e0).motto);
	p->emblem = (*(Setup*)g_7e23e0).emblem;
	cm_RequestCopyEntityData(p->id, spouse->id, 0x7f, 0);
	cm_RequestCopyEntityData(spouse->id, p->id, 0x7f, 0);
	cm_RequestCopyEntityData(p->id, child->id, 0x7f, 0);
	cm_RequestCopyEntityData(child->id, p->id, 0x7f, 0);
	cm_RequestCopyEntityData(spouse->id, child->id, 0x7f, 0);
	cm_RequestCopyEntityData(child->id, spouse->id, 0x7f, 0);
	cm_RequestMoveCredits(spouse->id, -1, (*(char*)&g_773d75), (gm_RandomMod(0x200) + 0x1f4) << 5);
	cm_RequestMoveCredits(child->id, -1, (*(char*)&g_773d75), (gm_RandomMod(0x200) + 0x1f4) << 5);
	if (g_6a3440 > -1) {
		gm_AllocMissionJob(p->id, (*(Setup*)g_7e23e0).dynasty, 0);
	}
	for (i = 0; i < 5; i++) {
		p->skills[i] = (*(Setup*)g_7e23e0).skills[i];
	}
}
unsigned char _dpad_7e1f70[1136];
unsigned char _dpad_7e23e0[304];
