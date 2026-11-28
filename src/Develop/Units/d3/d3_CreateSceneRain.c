extern char g_772f6c[];
extern char cut_SkipMode[];

int __cdecl d3_CreateRain(int);

/* ADDRESS: GOLDDE 0x004d15c0 */
void __cdecl d3_CreateSceneRain(int a1)
{
	if (*(int*) &cut_SkipMode == 0) {
		*(int*) &g_772f6c = d3_CreateRain(a1);
	}
}
