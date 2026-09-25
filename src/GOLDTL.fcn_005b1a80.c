// FUNCTION: GOLDTL 0x5b1a80
// SIZE: 27

char* __cdecl fcn_005b1a80(int key)
{
	char* p;

	p = *(char**) 0x774a78;
	while (p != 0) {
		if (*(int*) p == key) {
			return p;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}

void __cdecl fcn_005b1980(int a, char* o);

// FUNCTION: GOLDTL 0x005b1e20
// SIZE: 31

void __cdecl fcn_005b1e20(char* p)
{
	char* o;

	o = fcn_005b1a80(*(int*) (p + 1));
	if (o != 0) {
		fcn_005b1980((int) p, o);
	}
}
