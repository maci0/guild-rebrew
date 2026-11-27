extern char g_772f3c[];

int __cdecl fcn_00415310(int);

void __cdecl d3_CreateSceneRain(int a1)
{
	if (*(int*) &g_772f3c == 0) {
		*(int*) 0x772f6c = fcn_00415310(a1);
	}
}
