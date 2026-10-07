// FUNCTION: GOLD 0x005e7cfd
// fcn_005e7cfd — 1 if all three dwords zero, else 0.

int __cdecl fcn_005e7cfd(int* a)
{
	int i;
	for (i = 0; i < 3; i++) {
		if (a[i] != 0) {
			return 0;
		}
	}
	return 1;
}
