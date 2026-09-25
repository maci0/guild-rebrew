// FUNCTION: GOLDTL 0x510400
// SIZE: 104

void* __cdecl fcn_00502cd0(int, int, int, int, int);

int __cdecl fcn_00510400(char* p)
{
	int r;

	r = 1;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x27a) != 0) {
		r = 2;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x27b) != 0) {
		r++;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x292) != 0) {
		r++;
	}
	return r;
}
