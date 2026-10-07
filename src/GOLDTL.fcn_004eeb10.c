// FUNCTION: GOLD 0x4ecd10
// FUNCTION: GOLDTL 0x4eeb10

int __cdecl fcn_004eeb10(int* a1, char* a2)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (*(int*) (a2 + 0xc + i * 8) == a1[2]) {
			*(int*) (a2 + 0x10 + i * 8) = a1[4];
			return 1;
		}
	}
	return 0;
}
