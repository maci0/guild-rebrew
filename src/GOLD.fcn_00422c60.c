// FUNCTION: GOLD 0x00422c60
// fcn_00422c60 — free chain from [n][0xc].

int __cdecl fcn_00422620(int);

void __cdecl fcn_00422c60(char** n)
{
	char* p;
	p = *n;
	while (p != 0) {
		char* next;
		next = *(char**) (p + 0xc);
		fcn_00422620((int) p);
		p = next;
	}
	*n = 0;
}
