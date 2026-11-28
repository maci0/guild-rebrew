extern char cut_SkipMode[];

int __cdecl d3_CreateRain(int);

void __cdecl d3_CreateSceneRain(int a1)
{
	if (*(int*) &cut_SkipMode == 0) {
		*(int*) 0x772f6c = d3_CreateRain(a1);
	}
}
