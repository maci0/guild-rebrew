/* Walks a packed string list. a2 == 8 reads the count from *(int*)a1 and
 * returns the entry at index 4, or 6 when that entry is nonempty. */
/* ADDRESS: GOLD 0x0042c3b0 */
char* __cdecl fcn_0042c3b0(char* a0, int a1, int a2)
{
	char* base;
	char* alt;
	char* p;
	int n;
	int i;

	base = a0;
	if (a2 == 8) {
		n = *(int*) a1;
		alt = a0;
		a1 = (int) ((int*) a1 + 1);
	} else {
		alt = (char*) a1;
		n = a2;
	}
	n--;
	p = a0;
	i = 0;
	while (i < n) {
		while (*p != 0) {
			p++;
		}
		p++;
		if (p == (char*) 1) {
			return base;
		}
		i++;
		if (i == 4 || (i == 6 && *p != 0)) {
			alt = p;
		}
	}
	if (*p == 0 && a2 == 4) {
		return base;
	}
	if (*p == 0 && a2 == 8) {
		return alt;
	}
	return p;
}
