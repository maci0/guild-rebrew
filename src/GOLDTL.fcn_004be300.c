// FUNCTION: GOLDTL 0x4be300
// SIZE: 27

int __cdecl fcn_004be300(char* p, char* target)
{
	int n;

	for (n = 0; p != 0; n++) {
		if (target == p) {
			return n;
		}
		p = *(char**) (p + 0x3c);
	}
	return n;
}
