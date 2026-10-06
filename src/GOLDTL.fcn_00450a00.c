extern int g_6b86d4;
extern int g_6b8300;
// FUNCTION: GOLDTL 0x450a00

void __cdecl fcn_0043ef20(int);

void __cdecl fcn_00450a00(void)
{
	g_6b86d4++;
	if (g_6b8300 != 0) {
		fcn_0043ef20(g_6b8300);
	}
	g_6b86d4--;
}
