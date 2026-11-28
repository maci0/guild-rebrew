#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"







typedef struct Job {
	int op;
	int id;
	char pad8[0x1c];
} Job;
// SIZE 0x24

typedef struct Spec {
	int op;
	int level;
} Spec;

typedef struct Req {
	int id;
	int x4;
	int x8;
	int xc;
	int x10;
	char pad14[0x68];
} Req;
// SIZE 0x7c


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char gm_MissionJobs[];
extern signed char gm_SelectedMissionIndex;

Spec* __cdecl gm_LookupMissionSpec(int op);
void __cdecl d2_RunMissionBriefingDialog(Spec* s, int flags);
void __cdecl main_PlayOutroMovie(void);
int __cdecl d2_RunChooseHistoryLevelDialog(int n);
int __cdecl gm_AllocMissionJob(int a1, int a2, int a3);
int __cdecl cm_RequestSysMessage(int, Req*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl main_ExitToGameLoop(int flags);

/* ADDRESS: GOLDTL 0x004b62e0 */
void __cdecl d2_FinishHistoryMissionDialog(int flags)
{
	int level;
	Req m;
	ENTITY_RECORD* ent;
	Spec* s;
	int h;
	int i;
	int r;

	s = 0;
	level = -1;
	ent = &((ENTITY_RECORD*)gm_EntitySlotTable)[gm_LocalPlayerSlot];
	for (i = 0; i < 128; i++) {
		if (((Job*)gm_MissionJobs)[i].op != 0 && ((Job*)gm_MissionJobs)[i].id == ent->entity_id) {
			s = gm_LookupMissionSpec(((Job*)gm_MissionJobs)[i].op);
			level = s->level + 1;
			memset(&((Job*)gm_MissionJobs)[i], 0, sizeof(Job));
			break;
		}
	}
	flags = (flags & ~9) | 0x100;
	d2_RunMissionBriefingDialog(s, flags);
	main_PlayOutroMovie();
	r = d2_RunChooseHistoryLevelDialog(level);
	if (r == 0) {
		gm_SelectedMissionIndex = -1;
		m.id = ent->entity_id;
		m.x10 = 0;
		h = cm_RequestSysMessage(10, &m);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
	} else if (r == 0xff) {
		gm_SelectedMissionIndex = -1;
		m.id = ent->entity_id;
		m.x10 = 1;
		h = cm_RequestSysMessage(10, &m);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
		main_ExitToGameLoop(flags);
	} else {
		gm_AllocMissionJob(ent->entity_id, r, 1);
		m.id = ent->entity_id;
		m.x10 = 0;
		h = cm_RequestSysMessage(10, &m);
		while (cm_GetCommandStatus(h) == 0) {
			cm_StepCommandQueue();
		}
	}
}
