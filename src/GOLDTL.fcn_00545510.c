extern int g_7749d4;
extern char g_77e980[];
// FUNCTION: GOLDTL 0x00545510
// SIZE: 59

void __cdecl fcn_00546190(char*);

void __cdecl fcn_00545510(void)
{
	int i;

	for (i = 0; i <= g_7749d4 && i < 0x400; i++) {
		if (g_77e980[i * 0x14c] != 0) {
			fcn_00546190(g_77e980 + i * 0x14c);
		}
	}
}
