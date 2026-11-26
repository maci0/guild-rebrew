extern int g_7746a0;
extern int g_7746a0;



int __cdecl main_RunFrameLoop(void*, int);
int __cdecl fcn_0065f220(void*, int);
void __cdecl d2_RunTechTreeDialog(int, int);

void __cdecl d2_RunUpgradeTechTreeHud(int a)
{
	while (main_RunFrameLoop(d2_RunUpgradeTechTreeHud, 0x67fff)) {
		if (g_7746a0 != 0 && fcn_0065f220((void*) "UPGRADE", g_7746a0) == 0) {
			d2_RunTechTreeDialog(a, 0x2c);
		}
	}
}
