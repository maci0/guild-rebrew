// FUNCTION: GOLDTL 0x42df30
// SIZE: 49

int __cdecl fcn_0042df30(int a1, int a2)
{
	int i;
	int a;

	for (i = 0, a = 0x1052c60; a < 0x1052de0; a += 0xc, i++) {
		if (*(int*) a == a1) {
			((int*) 0x1052c68)[i * 3] = a2;
			return 1;
		}
	}
	return 0;
}
