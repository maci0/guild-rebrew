char* __cdecl fcn_004ac1e0(int);
unsigned short __cdecl gm_RandomMod(int);

// FUNCTION: GOLD 0x004ac170
// FUNCTION: GOLDTL 0x4ac290

unsigned short __cdecl fcn_004ac290(int id)
{
	unsigned short r;
	char* p;

	r = 0x1e2b;
	p = fcn_004ac1e0(id);
	if (p != 0) {
		if (*(int*) (p + 8) == 0)
			r = gm_RandomMod(10);
		else
			r = gm_RandomMod(10);
	}
	return r;
}
