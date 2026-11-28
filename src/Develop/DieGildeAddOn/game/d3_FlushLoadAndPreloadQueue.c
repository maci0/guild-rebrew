


extern int* lb_LobbyPlayerList;

int __cdecl cm_RequestClearSceneEntries(void);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int* __cdecl lb_GetPlayerList(void);
int __cdecl cm_RequestPreloadSceneEntry(int);

/* ADDRESS: GOLDDE 0x00579180 */
void __cdecl d3_FlushLoadAndPreloadQueue(void)
{
	int h;
	int r;
	int i;

	h = cm_RequestClearSceneEntries();
	while (cm_GetCommandStatus(h) == 0) {
		cm_StepCommandQueue();
	}
	lb_LobbyPlayerList = lb_GetPlayerList();
	r = -1;
	for (i = 1; i < 9; i++) {
		if (lb_LobbyPlayerList[i] != 0) {
			r = cm_RequestPreloadSceneEntry(lb_LobbyPlayerList[i]);
		}
	}
	if (r != -1) {
		while (cm_GetCommandStatus(r) == 0) {
			cm_StepCommandQueue();
		}
	}
}
