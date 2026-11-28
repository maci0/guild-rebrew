


// SIZE 0x24
typedef struct {
	int f0;
	int f4;
	int f8;
	char pad[0x14];
	char f20;
	char pad2[3];
} rec24;

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x7c
struct req {
	int who;
	char pad4[0x78];
};

extern signed char gm_SelectedMissionIndex;
extern char gm_MissionJobs[];

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl he_FreeAction(char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl gm_CheckMissionCondition(rec24*);
int __cdecl cm_RequestSysMessage(int, struct req*);
int __cdecl cm_GetCommandStatus(int);

/* ADDRESS: GOLDDE 0x0055b440 */
void __cdecl he_RunMissionCheck(char* u)
{
	struct req q;
	int i;
	int r;

	if ((*(char*)&gm_SelectedMissionIndex) <= -1) {
		he_FreeAction(u);
		return;
	}
	for (i = 0; i < 128; i++) {
		if (((rec24*)gm_MissionJobs)[i].f0 != 0 && ((rec24*)gm_MissionJobs)[i].f4 == ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id) {
			break;
		}
	}
	if (i >= 128) {
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 0x1e, 0);
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (((rec24*)gm_MissionJobs)[i].f20 == 0 && (unsigned short) gm_GameTime.b < 0x16 && gm_CheckMissionCondition(&((rec24*)gm_MissionJobs)[i]) != 0) {
			((rec24*)gm_MissionJobs)[i].f20 = 1;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
			*(int*) (u + 0x70) = 1;
			return;
		}
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 10, 0);
		return;
	case 1:
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
		if (((rec24*)gm_MissionJobs)[i].f20 == 1 && (unsigned short) gm_GameTime.b < 0x16 && g_6a3760 == -1) {
			q.who = ((rec24*)gm_MissionJobs)[i].f4;
			*(int*) (u + 0xac) = cm_RequestSysMessage(8, &q);
			*(int*) (u + 0x70) = 2;
			return;
		}
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 1, 0, 0);
		*(int*) (u + 0x70) = 1;
		return;
	case 2:
		r = cm_GetCommandStatus(*(int*) (u + 0xac));
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
		if (r == 0) {
			return;
		}
		if (r == 1) {
			*(int*) (u + 0x70) = 0;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
			return;
		}
		*(int*) (u + 0x70) = 1;
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 0x1e, 0);
		return;
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	}
}
