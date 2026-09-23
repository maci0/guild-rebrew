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
