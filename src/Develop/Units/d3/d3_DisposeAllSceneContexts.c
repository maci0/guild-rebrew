

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_ClearSceneState(void);

void __cdecl d3_DisposeAllSceneContexts(void)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		d3_SelectSceneContext(i, 0);
		d3_ClearSceneState();
	}
}
