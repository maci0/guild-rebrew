// FUNCTION: GOLD 0x005a8690
// fcn_005a8690 — find node [n]==a in 0x48 chain, return n+0xc or 0.

int __cdecl fcn_005a8690(int a)
{
	char* p;
	p = *(char**) 0x6f26c0;
	while (p != 0) {
		if (*(int*) p == a) {
			return (int) (p + 0xc);
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}
