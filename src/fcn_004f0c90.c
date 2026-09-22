// FUNCTION: GOLDTL 0x4f0c90
// SIZE: 48

int __cdecl fcn_004f0c90(int a1)
{
	int i;
	int a;

	i = 0;
	for (a = 0x7731b8; a < 0x773d38; a += 0x170, i++) {
		if (*(int*) a == a1) {
			return (int) (0x7731b8 + i * 368);
		}
	}
	return 0;
}
