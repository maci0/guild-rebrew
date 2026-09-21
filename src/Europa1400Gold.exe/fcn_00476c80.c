// FUNCTION: GOLD 0x00476c80
// SIZE: 25
// fcn_00476c80 — count != -1 over 0xf8ab80 (stride 0xc).

int __cdecl fcn_00476c80(void)
{
	int i;
	int c;
	c = 0;
	for (i = 0xf8ab80; i < 0xf8abc8; i += 0xc) {
		if (*(int*) i != -1) {
			c++;
		}
	}
	return c;
}
