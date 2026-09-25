// FUNCTION: GOLD 0x00577f20
// SIZE: 106
// FUNCTION: GOLDTL 0x005804f0
// SIZE: 106

extern int* g_665f08;
extern char g_6811b0[];

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);

void __cdecl fcn_005804f0(void)
{
	fcn_004727a0(g_665f08[13], 0);
	fcn_00519190(g_6811b0);
	fcn_00471af0(g_665f08[13], 0);
	if (g_665f08[5] != 0) {
		if (fcn_00423460(g_665f08[5]) != 0) {
			fcn_004237f0(g_665f08[5], 0);
		}
		g_665f08[5] = 0;
	}
}
