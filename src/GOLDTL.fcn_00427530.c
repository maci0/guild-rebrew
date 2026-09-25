// GLOBAL: GOLDTL 0x6b7ec0
extern int g_6b7ec0;
// GLOBAL: GOLD 0x6332e0
extern int g_6b7ec0;
// FUNCTION: GOLD 0x00428ca0
// SIZE: 51
// FUNCTION: GOLDTL 0x427530
// SIZE: 51

extern int g_6b7e98;

int __cdecl fcn_00428800(int);
int __cdecl fcn_00427b40(int);
void __cdecl fcn_00428720(int);

void __cdecl fcn_00427530(void)
{
	int x;

	x = fcn_00428800(0);
	if (fcn_00427b40(g_6b7e98) == 0) {
		fcn_00428720(g_6b7e98);
	}
	g_6b7ec0 = x;
}
