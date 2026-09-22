// FUNCTION: GOLDTL 0x4b3c80
// SIZE: 39

int __cdecl fcn_004b3c80(int a1)
{
	int p;

	for (p = 0x10069a4; p < 0x1007ba4; p += 0x24) {
		if (*(int*) (p - 4) != 0) {
			if (*(int*) p == a1) {
				return 1;
			}
		}
	}
	return 0;
}
