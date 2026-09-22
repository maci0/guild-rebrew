// FUNCTION: GOLDTL 0x4be340
// SIZE: 19

int __cdecl fcn_004be340(char* p)
{
	int n;

	n = 0;
	while (p != 0) {
		p = *(char**) (p + 0x3c);
		n++;
	}
	return n;
}
