// FUNCTION: GOLDTL 0x4246c0
// SIZE: 27

int __cdecl fcn_004246c0(void)
{
	char* p;
	int n;

	n = 0;
	p = *(char**) 0x6b7d68;
	p = *(char**) (p + 0x38);
	while (p != 0) {
		p = *(char**) (p + 0x104);
		n++;
	}
	return n;
}
