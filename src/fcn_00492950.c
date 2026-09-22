// FUNCTION: GOLDTL 0x492950
// SIZE: 63

int __cdecl fcn_00492950(char* p, int a2, int a3)
{
	int v;
	int e;

	if (a2 == *(int*) (p + 0xc)) {
		v = *(int*) (p + 0x28);
	} else if (a2 == *(int*) (p + 0x30)) {
		v = *(int*) (p + 0x4c);
	} else {
		return 0;
	}
	for (e = 0x6641a4; e < 0x6641ec; e += 8) {
		if (*(int*) (e - 4) == v && *(int*) e == a3) {
			return 1;
		}
	}
	return 0;
}
