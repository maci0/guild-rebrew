


extern int* g_774a34;

int __cdecl cm_RequestClearSceneEntries(void);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);
int* __cdecl fcn_004ce180(void);
int __cdecl cm_RequestPreloadSceneEntry(int);

void __cdecl d3_FlushLoadAndPreloadQueue(void)
{
	int h;
	int r;
	int i;

	h = cm_RequestClearSceneEntries();
	while (cm_GetCommandStatus(h) == 0) {
		fcn_00535960();
	}
	g_774a34 = fcn_004ce180();
	r = -1;
	for (i = 1; i < 9; i++) {
		if (g_774a34[i] != 0) {
			r = cm_RequestPreloadSceneEntry(g_774a34[i]);
		}
	}
	if (r != -1) {
		while (cm_GetCommandStatus(r) == 0) {
			fcn_00535960();
		}
	}
}
