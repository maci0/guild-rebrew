// FUNCTION: GOLDTL 0x422aa0
// SIZE: 48

char* __cdecl fcn_00422aa0(void)
{
	char* p;

	p = *(char**) 0x6b7d78;
	if (*(int*) 0x6b7d7c == 0) {
		return (char*) 0x14cb980;
	}
	if (p != 0) {
		while (*(char**) (p + 0x13c) != 0) {
			p = *(char**) (p + 0x13c);
		}
	}
	return p;
}
