#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include <string.h>

// SIZE 0x40
typedef struct {
	int id[16];
} Ids;

// SIZE 0x48
typedef struct {
	int who;
	Ids ids;
	int pad;
} Msg;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl cm_RequestRemoveCutsceneParticipant(int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
void __cdecl cm_SendLogAction(char*);
int __cdecl cm_RequestCutsceneReady(Msg*);
void __cdecl cm_SendTraceEnd(char*);


/* ADDRESS: GOLDTL 0x004e64e0 */
int __cdecl cut_CutsceneReady(int* c)
{
	Msg m;
	char* o;
	int i;
	int h;

	memset(&m, 0, sizeof(m));
	if ((*((unsigned char*) c + 0x26) & 0x80) == 0) {
		h = -1;
		for (i = 0; i < *((unsigned char*) c + 0x30); i++) {
			if (c[13 + i] != -1) {
				o = gm_LookupEntityRecordById(c[13 + i]);
				if (o == 0 || (*(int*) (o + 0x20c) != -1 && *(int*) (o + 0x20c) != c[0] && (o[2] == 6 || o[2] == 7)))
					h = cm_RequestRemoveCutsceneParticipant(c[0], c[13 + i]);
			}
		}
		if (h != -1) {
			do {
				if (cm_GetCommandStatus(h) != 0)
					break;
				cm_StepCommandQueue();
			} while (1);
		}
	} else {
		for (i = 0; i < *((unsigned char*) c + 0x30); i++) {
			if (c[13 + i] != -1) {
				o = gm_LookupEntityRecordById(c[13 + i]);
				if (o != 0 && *(int*) (o + 0x20c) != -1 && *(int*) (o + 0x20c) != c[0] && (o[2] == 6 || o[2] == 7))
					return 0;
			}
		}
	}
	if (cut_CheckMaster(c) == 0)
		return -1;
	m.who = c[0];
	m.ids = *(Ids*) (c + 13);
	cm_SendLogAction("cut_CutsceneReady");
	h = cm_RequestCutsceneReady(&m);
	cm_SendTraceEnd("cut_CutsceneReady");
	while (cm_GetCommandStatus(h) == 0)
		cm_StepCommandQueue();
	return cm_GetCommandStatus(h) != 2;
}
