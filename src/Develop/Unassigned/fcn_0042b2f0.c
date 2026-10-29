/* ADDRESS: GOLDTL 0x0042b2f0 */
char* __cdecl fcn_0042b2f0(char* base, int count, int mode)
{
	char c;
	char* sel;
	char* p;
	int n;
	int i;

	c = (char) mode;
	p = base;
	n = 0;
	if (c == 8) {
		count += 4;
		sel = base;
	} else {
		sel = (char*) mode;
	}
	while (n < count - 1) {
		i = 0;
		while (p[i] != 0) {
			i++;
		}
		p = p + i - 1;
		if (p == 0) {
			return base;
		}
		p++;
		n++;
		if (n == 4 || (n == 6 && *p != 0)) {
			sel = p;
		}
	}
	if (*p == 0) {
		if (c == 4) {
			return base;
		}
		if (c == 8) {
			p = sel;
		}
	}
	return p;
}
