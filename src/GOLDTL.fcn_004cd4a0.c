char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004030e0(char*);

// FUNCTION: GOLD 0x4cc920
// FUNCTION: GOLDTL 0x4cd4a0

int __cdecl fcn_004cd4a0(char* a1, char* a2)
{
	char* e;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	e = fcn_00508e40(*(int*) (a1 + 0x10));
	if (e != 0 && *(char**) (e + 0x184) != 0) {
		fcn_004030e0(*(char**) (e + 0x184));
		*(char**) (e + 0x184) = 0;
		if (a2 != 0)
			a2[0] = 1;
		return 0;
	}
	return 1;
}
