// FUNCTION: GOLD 0x005241f0
// SIZE: 30
// fcn_005241f0 — count != -1 in 8 ints at a+0x8c.

int __cdecl fcn_005241f0(char* a)
{
	int i;
	int c;
	c = 0;
	for (i = 0; i < 8; i++) {
		if (*(int*) (a + 0x8c + i * 4) != -1) {
			c++;
		}
	}
	return c;
}
