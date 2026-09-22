// FUNCTION: GOLDTL 0x4b3cb0
// SIZE: 41

int __cdecl fcn_004b3cb0(int a1)
{
	int count;
	int p;

	if (a1 < 0 || a1 > 5) {
		return -1;
	}
	count = 0;
	for (p = 0x680bd4; p < 0x681114; p += 0x1c) {
		if (*(int*) p == a1) {
			count++;
		}
	}
	return count;
}
