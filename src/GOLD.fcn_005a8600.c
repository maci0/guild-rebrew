// FUNCTION: GOLD 0x005a8600
// fcn_005a8600 — list search for [node]==a, by 0x48 chain.

int __cdecl fcn_005a8600(int a)
{
	char* c;
	c = *(char**) 0x6f26c0;
	while (c != 0) {
		if (*(int*) c == a) {
			return (int) c;
		}
		c = *(char**) (c + 0x48);
	}
	return 0;
}
