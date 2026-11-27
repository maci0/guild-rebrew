

void __cdecl d3_SelectSceneContext(int, int);
void __cdecl fcn_00442e30(void);

void __cdecl d3_DisposeAllSceneContexts(void)
{
	int i;

	for (i = 0; i < 0x40; i++) {
		d3_SelectSceneContext(i, 0);
		fcn_00442e30();
	}
}
