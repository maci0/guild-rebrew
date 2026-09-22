// FUNCTION: GOLDTL 0x4cef70
// SIZE: 59

int __cdecl fcn_004cef70(int a1, char* a2)
{
	int r;

	r = 0;
	if (*(int*) (a2 + 0x16c) == (int) (0x7f4ca0 + a1 * 540)) {
		r = 0x800;
	}
	if (*(int*) 0x774800 != 0) {
		r = 0x800;
	}
	return r;
}
