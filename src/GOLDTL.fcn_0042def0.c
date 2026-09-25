// FUNCTION: GOLDTL 0x42def0
// SIZE: 49
int __cdecl fcn_0042def0(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x1052c60; a < 0x1052de0; a += 0xc, i++) {
		if (*(int*) a == a1) {
			((int*) 0x1052c60)[i * 3] = 0;
			return 1;
		}
	}
	return 0;
}
