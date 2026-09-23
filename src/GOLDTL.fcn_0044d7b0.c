// FUNCTION: GOLDTL 0x44d7b0
// SIZE: 38

int __cdecl fcn_0044d7b0(int a1, int* p)
{
	int i;

	for (i = 0; i < 0x40; i++, p += 3) {
		if (a1 == *p) {
			return i;
		}
		if (*p == 0x28) {
			break;
		}
	}
	return 0x27;
}
