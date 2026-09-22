// FUNCTION: GOLDTL 0x4246e0
// SIZE: 24

int __cdecl fcn_004246e0(void)
{
	char* p;
	int n;

	n = 0;
	p = *(char**) 0x6b7d68;
	p = *(char**) (p + 0x3c);
	while (p != 0) {
		p = *(char**) (p + 0x3c);
		n++;
	}
	return n;
}
