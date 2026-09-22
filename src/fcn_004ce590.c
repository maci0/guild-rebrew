// FUNCTION: GOLDTL 0x4ce590
// SIZE: 45

int __cdecl fcn_004ce590(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x68b400; a < 0x68b798; a += 0x5c, i++) {
		if (*(int*) a == a1) {
			return (int) (0x68b400 + i * 92);
		}
	}
	return 0;
}
