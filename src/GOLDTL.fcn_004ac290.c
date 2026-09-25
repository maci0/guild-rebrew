char* __cdecl fcn_004ac1e0(int);
unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLD 0x004ac170
// SIZE: 45
// FUNCTION: GOLDTL 0x4ac290
// SIZE: 45

unsigned short __cdecl fcn_004ac290(int id)
{
	unsigned short r;
	char* p;

	r = 0x1e2b;
	p = fcn_004ac1e0(id);
	if (p != 0) {
		if (*(int*) (p + 8) == 0)
			r = fcn_0042e410(10);
		else
			r = fcn_0042e410(10);
	}
	return r;
}
