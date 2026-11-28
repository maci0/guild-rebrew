#include "Develop/DieGildeAddOn/game/event_callbacks.h"
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl cm_RequestSetCutsceneMaster(int*, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);


/* ADDRESS: GOLDTL 0x004e63e0 */
/* ADDRESS: GOLDDE 0x004d2c30 */
int __cdecl cut_CheckMaster(int* event)
{
	int flag;
	char buf[0x80];
	char* e;
	int i;
	int r;

	if (cut_IsParticipant(event[3], (unsigned char*) event) == 0) {
		flag = 1;
		e = gm_LookupEntityRecordById(event[3]);
		fcn_0064d41a(buf, "cut_CheckMaster(): invalid master for id %i", event[0]);
		for (i = 0; i < 16; i++) {
			if (flag == 0)
				break;
			if (event[i + 13] != -1) {
				e = gm_LookupEntityRecordById(event[i + 13]);
				if (e != 0 && (e[2] == 6 || e[2] == 7))
					flag = 0;
			}
		}
		if (e != 0 && *(int*) (e + 4) != event[3]) {
			fcn_0064d41a(buf, "cut_CheckMaster(): new master for id %i => %i", event[0], *(int*) (e + 4));
			r = cm_RequestSetCutsceneMaster(event, e);
			while (cm_GetCommandStatus(r) == 0)
				cm_StepCommandQueue();
			return 0;
		}
	}
	return 1;
}
