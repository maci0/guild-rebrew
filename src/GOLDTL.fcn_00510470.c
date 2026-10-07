// FUNCTION: GOLD 0x0050cfd0
// FUNCTION: GOLDTL 0x510470

void* __cdecl fcn_00502cd0(int, int, int, int, int);

int __cdecl fcn_00510470(char* p)
{
	int r;

	r = 2;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x274) != 0) {
		r = 3;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x27e) != 0) {
		r++;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x28e) != 0) {
		r++;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x291) != 0) {
		r++;
	}
	return r;
}
