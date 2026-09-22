// FUNCTION: GOLDTL 0x4e51a0
// SIZE: 33

int __cdecl fcn_004e51a0(char* a1, int a2)
{
	int i;

	for (i = a2 - 1; i > 0; i--) {
		if (*(int*) (a1 + 0x34 + i * 4) != -1) {
			return i;
		}
	}
	return 0;
}
