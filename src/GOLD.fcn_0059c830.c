/* ADDRESS: GOLD 0x0059c830 */
/* ADDRESS: GOLDTL 0x005a59b0 */

// fcn_0059c830 — count non-(-1) of 16 entries (stride 0x1c).

int __cdecl fcn_0059c830(char* a)
{
	int i;
	int c;
	c = 0;
	for (i = 0; i < 0x10; i++) {
		if (*(int*) (a + i * 0x1c) != -1) {
			c++;
		}
	}
	return c;
}

