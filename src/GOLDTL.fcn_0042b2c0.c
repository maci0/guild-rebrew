// FUNCTION: GOLDTL 0x42b2c0
// SIZE: 25

int __cdecl fcn_0042b2c0(void)
{
	int a;
	int n;

	n = 0;
	for (a = 0x6b7ed0; a < 0x6b7f10; a += 4) {
		if (*(int*) a != 0) {
			n++;
		}
	}
	return n;
}
