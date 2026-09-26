// FUNCTION: GOLD 0x0042bb00
// SIZE: 57
// FUNCTION: GOLDTL 0x42a460
// SIZE: 57

extern int g_6b7f90;
extern int* g_6b7ed0[16];

void __cdecl fcn_0042a410(int, int, int);

void __cdecl fcn_0042a460(int a1, int a2)
{
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) g_6b7ed0; a < (int) (g_6b7ed0 + 16); a += 4) {
			if (*(int*) a != 0) {
				fcn_0042a410(*(int*) a, a1, a2);
			}
		}
	}
}
