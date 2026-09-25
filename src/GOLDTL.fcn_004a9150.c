int __cdecl fcn_004f39b0(int);

// FUNCTION: GOLDTL 0x4a9150
// SIZE: 71

int __cdecl fcn_004a9150(int a, char* e, int b, char* out)
{
	int n;
	int h;

	if (*(int*) (e + 0x194) < 2)
		return 0;
	n = fcn_004f39b0(*(int*) (e + 4));
	if (n <= 0)
		return 0;
	h = *(int*) (e + 0x194) / 2;
	if (h >= n)
		h = n;
	*(int*) (out + 0x10) = h;
	return 1;
}
