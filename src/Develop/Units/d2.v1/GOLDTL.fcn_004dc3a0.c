/* Session cutscene command: resolves up to four participant entities, builds
 * the cutscene dialog and runs its message loop until the user leaves it. */

extern char* g_77255c;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1dc;
#include "client_dialog_state.h"

int __cdecl amt_FindOfficeSlotByKey(char*, void*);
int __cdecl amt_GetRoleTemplate(int, void*);
int __cdecl amt_CollectOfficeCandidates(int, int, void*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ai_SelectOfficeCandidate(char*, int, int*, void*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
unsigned int __cdecl io_AppendText();
int __cdecl d2_GetWindowListItem(int, int, char*);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl d2_UpdateProgressBar(int, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x004dc3a0 */
int __cdecl cut_ShowSessionDialog(char* a0, int a1, int* entityIds, int* a3)
{
	char info[0x18];
	char buf[24];
	void* ents[4];
	int handles[4];
	int ret;
	int n;
	int i;
	int found;
	int gui;
	int result;

	*a3 = 0;
	if (amt_FindOfficeSlotByKey(a0, info) == 0) {
		return -1;
	}
	if (amt_GetRoleTemplate(*(int*) (info + 8) & 0xff, buf) == 0) {
		return -1;
	}
	n = amt_CollectOfficeCandidates(*(int*) (info + 8) & 0xff, 2, ents);
	i = 0;
	found = 0;
	for (; i < 4; i++) {
		char* e;

		e = gm_LookupEntityRecordById(entityIds[i]);
		if (e != 0) {
			ents[found] = e;
			found++;
		}
	}
	if (found == 0) {
		return -1;
	}
	result = ai_SelectOfficeCandidate(a0, a1, entityIds, &ret);
	gui = fcn_00470820(0, 0, (char*) 0x68c340);
	fcn_00471d80(gui, 1);
	d2_SetForm(gui, 0);
	if (n < 2) {
		io_AppendText(0x12dc, *(unsigned short*) a1, *(unsigned short*) a1,
		    (*(int*) (info + 8) & 0xff) + 0x253);
	} else {
		io_AppendText(0x12dd, *(unsigned short*) a1, *(unsigned short*) a1,
		    (*(int*) (info + 8) & 0xff) + 0x253);
	}
	for (i = 0; i < found; i++) {
		handles[i] = d2_GetWindowListItem(gui, 0,
		    (char*) io_AppendText(0x68c354, *(unsigned short*) ents[i]));
	}
	for (i = found; i < 4; i++) {
		handles[i] = -1;
	}
	n = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100,
	    0x75, 0x42, d2_CurrentWindowId);
	d2_UpdateProgressBar(n, 0x5dc, 1);
	g_100f1dc = -1;
	while (main_RunFrameLoop((void*) 0x4dc230, cut_EventLoopFlags) != 0) {
		if (d2_UpdateProgressBar(n, 0, 0) != 0) {
			if (g_100f1dc != -1) {
				for (i = 0; i < found; i++) {
					if (d2_CurrentElementId == handles[i]) {
						result = *(int*) ((char*) ents[i] + 4);
						goto setflag;
					}
				}
			}
			goto next;
		}
setflag:
		g_774654 = 1;
next:
		;
	}
	d2_DestroyForm(gui);
	return result;
}
