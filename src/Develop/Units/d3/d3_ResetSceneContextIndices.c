extern char init_SceneContextIndices[];
extern char init_SceneContextIndices[];
extern signed char g_7f3b00[];
extern signed char g_7f3b00[];

/* ADDRESS: GOLD 0x0050d460 */
/* ADDRESS: GOLDTL 0x00510900 */
char __cdecl d3_ResetSceneContextIndices(void)
{
	int i;

	for (i = 0; i < 0xb7; i++) {
		((int*) init_SceneContextIndices)[i] = -1;
	}
	for (i = 0; i < 17; i++) {
		((short*) g_7f3b00)[i] = -1;
	}
	return 0;
}
