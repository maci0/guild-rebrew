// FUNCTION: GOLDTL 0x42df70
// SIZE: 49

int __cdecl fcn_0042df70(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x1052c60; a < 0x1052de0; a += 0xc, i++) {
		if (*(int*) a == a1) {
			return ((int*) 0x1052c68)[i * 3] != 0;
		}
	}
	return 0;
}
