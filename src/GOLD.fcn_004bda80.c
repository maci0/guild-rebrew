// FUNCTION: GOLD 0x004bda80
// fcn_004bda80 — count nodes from a to b (by 0x3c chain), else 0.

int __cdecl fcn_004bda80(char* a, char* b)
{
	int c;
	c = 0;
	while (a != 0 && a != b) {
		c++;
		a = *(char**) (a + 0x3c);
	}
	return c;
}
