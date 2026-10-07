// FUNCTION: GOLD 0x004ccbd0
// FUNCTION: GOLDTL 0x4cd750

int __cdecl fcn_004e8810(char*);

int __cdecl fcn_004cd750(char* a1, char* a2)
{
	int r;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	r = fcn_004e8810(a1 + 0x10);
	if (a2 != 0 && r != 0) {
		*a2 = 1;
	}
	if (r != 0) {
		return 0;
	}
	return 1;
}
