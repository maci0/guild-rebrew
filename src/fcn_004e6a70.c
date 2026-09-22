// FUNCTION: GOLDTL 0x4e6a70
// SIZE: 50

int __cdecl fcn_004e6a70(int a1)
{
	int i;
	int a;

	i = 0;
	for (a = 0x9b0e30; a < 0x9b43f0; a += 0x35c, i++) {
		if (*(int*) a == a1) {
			return (int) (0x9b0e20 + i * 860);
		}
	}
	return 0;
}
