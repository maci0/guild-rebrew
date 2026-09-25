// FUNCTION: GOLDTL 0x42a460
// SIZE: 57

void __cdecl fcn_0042a410(int, int, int);

void __cdecl fcn_0042a460(int a1, int a2)
{
	int a;

	if (*(int*) 0x6b7f90 != 0) {
		for (a = 0x6b7ed0; a < 0x6b7f10; a += 4) {
			if (*(int*) a != 0) {
				fcn_0042a410(*(int*) a, a1, a2);
			}
		}
	}
}
