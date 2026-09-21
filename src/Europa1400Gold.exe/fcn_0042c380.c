// FUNCTION: GOLD 0x0042c380
// SIZE: 25
// fcn_0042c380 — count non-zero ints at 0x6332f0 (16 entries).

int __cdecl fcn_0042c380(void)
{
	int i;
	int c;
	c = 0;
	for (i = 0; i < 0x10; i++) {
		if (*(int*) ((char*) 0x6332f0 + i * 4) != 0) {
			c++;
		}
	}
	return c;
}
