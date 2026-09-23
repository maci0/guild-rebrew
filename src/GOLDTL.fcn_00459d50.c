// FUNCTION: GOLDTL 0x459d50
// SIZE: 57

int __cdecl fcn_00459d50(char* p)
{
	int r;
	int n;

	r = 0;
	if (p != 0) {
		r = 0x34;
		if (*(int*) (p + 0x28) != 0) {
			n = *(int*) (p + 0x20);
			r += n * n;
		}
		if (*(int*) (p + 0x24) != 0) {
			n = *(int*) (p + 0x20);
			r += n * n * 7 * 4;
		}
	}
	return r;
}
