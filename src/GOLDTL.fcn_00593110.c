// FUNCTION: GOLDTL 0x00593110

extern int g_6a9b9c;
extern int g_6a9b94;
extern int g_772514;
extern int g_14b5d48;
extern int g_14b5d4c;
extern int g_14b5d50;
extern int g_9baadc;
extern char* g_1015ea0;
extern char g_6a9b90[];
extern char g_6a9b98[];

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00533a60(int, int, char*, int, ...);

void __cdecl fcn_00593110(void)
{
	fcn_004727a0(g_6a9b9c, 4);
	fcn_00533a60(g_772514, 0, g_6a9b90, 2, g_14b5d48, g_14b5d4c);
	fcn_004727a0(g_6a9b9c, 8);
	fcn_00533a60(g_772514, 0, g_6a9b98, 1, g_14b5d50);
	if (g_9baadc == 0x7f) {
		*(int*) (g_1015ea0 + g_6a9b94 * 756 + 0x4c) = 1;
	}
}
