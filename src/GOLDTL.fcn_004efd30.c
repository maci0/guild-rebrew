// FUNCTION: GOLDTL 0x4efd30
// SIZE: 53

int __cdecl fcn_004efd30(int a1)
{
	int i;
	int a;

	if (a1 == -1) {
		return 0;
	}
	i = 0;
	for (a = 0x7731b8; a < 0x773d38; a += 0x170, i++) {
		if (*(int*) a == a1) {
			return (int) (0x7731b8 + i * 368);
		}
	}
	return 0;
}
